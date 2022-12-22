/*
 * mae.c
 *
 *  Created on: 6 mai 2022
 *  Author : Emilien
 *
*/

#include "mae.h"
#include "globale.h"
#include "parse_LCD.h"
#include "frame_request.h"
#include "command.h"
#include "prechauffage.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include <math.h>

extern unsigned int valeur_slider ;
extern unsigned int size; // retournera la taille en octets du message à transmettre


//MOTEUR
t_parse_error recu_mae;
uint32_t read_value_mae = 0;

int etat, etat_calibrage;
unsigned char etat_procedure_prechauffage;

//UTILE POUR LA TRAME RECU DU LCD
char type = UK;
char nb = 0;
unsigned int valeur_flag;


void evolution_mae(unsigned char *etat_mae,char *frame)
{
/*
/	Fait évoluer l'état actuel de la machine à état en fonction de certaines conditions
/   Paramètres:
/   *etat_mae: état actuel de la machine à états
*/


//form 1 : Accueil						//Button 47 : START etatPrechauffage
//form 2 : ModeManuel					//Button 14 : ANNULE etatPrechauffage
//form 3 : ModeAuto						//Button 31 : START etatCalibrage
//form 4 : ModeLibre					//Button 32 : ANNULE etatCalibrage
//form 5 : Paramètre
//form 8 : CalibrageLongueur			//Forms Suplémentaires :
//form 10 : TempsPrechauffage								//form 6 : Info Plus Mode AUTO
//form 12 : PositionsPredefinies							//form 9 : Attente Moteur INIT


	nb=0;
	etat=1;
	type=UK;

	etat = parse_LCD(frame, &type, &nb, &valeur_slider, &valeur_flag); //décortique la trame et retourne les informations importantes

	if(reset_all==1)
	{
		Reset_All();
		*etat_mae=etatAccueil;
		etat=OK;
		nb=0;
		reset_all=0;
	}
	if(pos_init==1)///Utile uniquement au démarage et ativé par l'état defaut
	{
		HAL_Delay(100);
		if(recu_mae == ERR_SUCCESS)
		{
			recu_mae = command(1, ID_MOT_2, CMD_RESET_POSITION, 0x00, &read_value_mae);
		}

		if(recu_mae == ERR_SUCCESS)
		{
			recu_mae = command( 1, ID_MOT_2, CMD_GOTO, (50-43+2)/(0.001165*DIVISEUR_STEP_1), &read_value_mae);
		}


		frame_display_led(frame,&size, 0x00, 1); // LED 0 dans la form Temps prechauffage HOME Activé
		HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

		nform=0;//form ecran
		HAL_Delay(300);

		frame_display_change_form(frame,&size, nform) ;
		HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
		HAL_Delay(100);

		etat=OK;
		*etat_mae=etatAccueil;
		pos_init=0;
	}

	if(etat == OK)
	{
	switch(*etat_mae)
	{
		case etatAccueil :
			if (type == FORM)
			{
				switch(nb)
				{
					case 2 :
						*etat_mae=etatMANUEL;
						break;
					case 3:
						*etat_mae=etatAUTO;
						break;
					case 4:
						*etat_mae=etatLIBRE;
						break;
					case 5:
						*etat_mae=etatParametres;
						break;
				}
			}
			break;

		case etatAUTO :

			if (type == FORM)
			{
				switch(nb)
				{
					case 1 :
						*etat_mae=etatAccueil;
						break;
				}
			}
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 47 ://START procédure
						fin_procedure_prechauffage=0;
						*etat_mae=etatPrechauffage;

						//////////////// PROCEDURE LANCE //////////////////////////
						frame_display_led(frame,&size, 0x0B, 1); // LED 11
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);

						////////////////////   HOME   /////////////////////////////
						disponible=0;
						HAL_Delay(30);
						recu_mae = command(1, ID_MOT_2, CMD_HOME, 0x1800, &read_value_mae);
						HAL_Delay(120);//avoir le temps de voir que le moteur est en mvt ou pas

						break;
				}
			}
			break;


		case etatPrechauffage:
			if (fin_procedure_prechauffage==1)
			{
				*etat_mae=etatAUTO;
			}
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 14 ://ANNULE
						//////Tout remettre à 0
						fin_procedure_prechauffage=1;
						HAL_Delay(10);
						minuteur_en=0;

						frame_display_led(frame,&size, 0x0B, 0); // LED 11
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(100);
						frame_display_led(frame,&size, 0x0A, 0); // LED 10
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(100);
						frame_display_led(frame,&size, 0x09, 0); // LED 9
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(100);
						frame_display_led(frame,&size, 0x08, 0); // LED 8
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(100);
						frame_display_led(frame,&size, 0x03, 0); // LED 3
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(100);
						*etat_mae=etatAUTO;
						break;
				}
			}
			break;


		case etatMANUEL:
			if (type == FORM)
			{
				switch(nb)
				{
					case 1 :
						*etat_mae=etatAccueil;
						break;
				}
			}
			break;


		case etatLIBRE:
			if (type == FORM)
			{
				switch(nb)
				{
					case 1 :
						*etat_mae=etatAccueil;
						break;
				}
			}
			break;

		case etatParametres:
			if (type == FORM)
			{
				switch(nb)
				{
					case 1 :
						*etat_mae=etatAccueil;
						break;
					case 8:
						*etat_mae=etatCalibrageLongueur;
						nform=8;
						break;
					case 10:
						*etat_mae=etatTempsPrechauffage;
						break;
					case 12:
						*etat_mae=etatPositionsPredefinies;
						break;
				}
			}
			break;




		case etatCalibrageLongueur:

			frame_display_led(frame,&size, 0x0C, 0); // LED EN COURS
			HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
			HAL_Delay(100);

			frame_display_led(frame,&size, 0x0D, 0); // LED FIN CALIBRAGE
			HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
			HAL_Delay(100);

			if (type == FORM)
			{
				switch(nb)
				{
					case 5 :
						*etat_mae=etatParametres;
						break;
				}
			}
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 31 ://START
						fin_procedure_calibrage=0;
						start_calibrage=1;
						*etat_mae=etatCalibrage;
						etat_calibrage=Init_Calibrage;

						frame_display_led(frame,&size, 0x0C, 1); // LED EN COURS
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);

						break;
				}
			}
			break;


		case etatCalibrage:
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 32://ANNULE
						fin_procedure_calibrage=1;
						recu_mae = command( 1, ID_MOT_2, CMD_SOFT_STOP, 0x1800, &read_value_mae);
						*etat_mae=etatCalibrageLongueur;
						etat_calibrage=Fin_Calibrage;
						start_calibrage=0;

						frame_display_led(frame,&size, 0x0D, 1); // LED FIN CALIBRAGE
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);

						frame_display_led(frame,&size, 0x0C, 0); // LED EN COURS
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);

						break;
				}
			}
			break;

		case etatTempsPrechauffage:
			if (type == FORM)
			{
				switch(nb)
				{
					case 5 :
						*etat_mae=etatParametres;
						break;
				}
			}
			break;

		case etatPositionsPredefinies:
			if (type == FORM)
			{
				switch(nb)
				{
					case 5 :
						*etat_mae=etatParametres;
						break;
				}
			}
			break;
	}
	}
}





////////////////////////////////////////////////////
////		_____________________________		////
////		|							|		////
////		|		ACTION MAE			|		////
////		|___________________________|		////
////											////
////////////////////////////////////////////////////


void action_mae(unsigned char *etat_mae, char *frame)
{

	//etat = parse_LCD(frame, &type, &nb, &valeur_slider, &valeur_flag); //décortique la trame et retourne les informations importantes

	switch(*etat_mae)
	{
		case etatAUTO :
			nform=3;//form ecran
			if (type == BUTTON)
			{
				switch(nb)
				{
				case 15:
					//+100h
					HAL_Delay(10);
					if(heure_process>=999)
						heure_process=250;
					else
						heure_process+=100;
					break;

				case 16:
					//-100h
					HAL_Delay(10);
					if(heure_process<100)
					{
						heure_process=0;
						min_process=0;
					}
					else
						heure_process-=100;
					break;

				case 66:
					//+10h
					HAL_Delay(10);
					if(heure_process>=999)
						heure_process=250;
					else
						heure_process+=10;
					break;

				case 67:
					//-10h
					HAL_Delay(10);
					if(heure_process<10)
					{
						heure_process=0;
						min_process=0;
					}
					else
						heure_process-=10;
					break;

				case 68:
					//+1h
					HAL_Delay(10);
					if(heure_process>=999)
						heure_process=250;
					else
						heure_process+=1;
					break;

				case 71:
					//-1h
					HAL_Delay(10);
					if(heure_process<1)
					{
						heure_process=0;
						min_process=0;
					}
					else
						heure_process-=1;
					break;

				case 69:
					//+10 min_process
					HAL_Delay(10);
					if(min_process>=50)
					{
						min_process=(min_process+10)-60;
						heure_process+=1;
					}
					else
						min_process+=10;
					break;

				case 72:
					//-10 min_process
					HAL_Delay(10);
					if((min_process<=10)&&(heure_process>=1))
					{
						min_process=(60+min_process)-10;
						heure_process-=1;
					}
					else if ((min_process<=10) && (heure_process<1))
					{
						min_process=0;
					}
					else
						min_process-=10;
					break;

				case 70:
					//+1 min_process
					HAL_Delay(10);
					if(min_process>=59)
					{
						min_process=0;
						heure_process+=1;
					}
					else
						min_process+=1;
					break;

				case 73:
					//-1 min_process
					HAL_Delay(10);
					if((min_process<=1)&&(heure_process>=1))
					{
						min_process=59;
						heure_process-=1;
					}
					else if ((min_process<=1) && (heure_process<1))
					{
						min_process=0;
					}
					else
						min_process-=1;
					break;

				case 74:
					//Reset
					HAL_Delay(10);
					heure_process=0;
					min_process=0;
					break;
				}
			}
			break;

		case etatPrechauffage:

			prechauffage_moteur(&etat_procedure_prechauffage);
			break;

		case etatMANUEL:
			nform=2;//form ecran
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 5:
						//Avance
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_RUN_FORWARD, 0x1800, &read_value_mae);
						break;
					case 6:
						//RECULE
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_RUN_BACKWARD, 0x1800, &read_value_mae);
						break;
					case 8:
						//STOP DOUCEMENT
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_SOFT_STOP, 0x1800, &read_value_mae);
						break;

					case 7:
						//HOME
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_HOME, 0x1800, &read_value_mae);
						break;
					case 12:
						//MILIEU
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_GOTO, (position_milieu-43+2)/(0.001165*DIVISEUR_STEP_1), &read_value_mae);
																	// 183 -> distance en mm à parcourir sur le rail (entre le FDC et la pos sur le rail)
																	// 46 -> distance entre le FDC et le milieu du plateau
																	// +2 -> petite correction
																	// (0.001165*16) -> permet d'envoyer la valeur correct au moteur
						break;
					case 9:
						//ENTREE FOUR
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_GOTO, (position_entree_four-43)/(0.001165*DIVISEUR_STEP_1), &read_value_mae);
						break;
					case 11:
						//PROCESS
						HAL_Delay(10);
						recu_mae = command(1, ID_MOT_2, CMD_GOTO, (position_pocess-43-1)/(0.001165*DIVISEUR_STEP_1), &read_value_mae);// -1 -> petite correction
						break;
				}
			}
			break;

		case etatLIBRE:
			nform=4;//form ecran
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 19:
						//HIZ
						HAL_Delay(10);
						recu_mae = command( 1, ID_MOT_2, CMD_SOFT_HIZ, 0x00, &read_value_mae);
						break;
				}
			}
			break;

		case etatCalibrage:
			nform=8;//forme ecran

			//////// Re-AVANCE puis se remet en position /////////////////

			/*recu_mae = command( 1, ID_MOT_2, CMD_GOTO, 0x5EE, &read_value_mae);//90°
			HAL_Delay(1000);
			recu_mae = command( 1, ID_MOT_2,  CMD_RUN_BACKWARD, 0x1200, &read_value_mae);
			HAL_Delay(30);

			while(fin_de_course_home!=1);
			recu_mae = command( 1, ID_MOT_2, CMD_SOFT_STOP, 0x00, &read_value_mae);*/


			if(start_calibrage==1)
			{
				switch(etat_calibrage)
				{
				case Init_Calibrage:
					HAL_Delay(10);
					recu_mae = command( 1, ID_MOT_2, CMD_RUN_BACKWARD, 0x1800, &read_value_mae);
					HAL_Delay(30);
					if(fin_de_course_home==1)
					{
						etat_calibrage=Etape_1_Calibrage;
						recu_mae = command( 1, ID_MOT_2, CMD_HARD_STOP, 0x00, &read_value_mae);
						HAL_Delay(30);
						recu_mae = command( 1, ID_MOT_2, CMD_RESET_POSITION, 0x00, &read_value_mae);
						HAL_Delay(30);
						recu_mae = command( 1, ID_MOT_2, CMD_RUN_FORWARD, 0x1800, &read_value_mae);
						HAL_Delay(30);
					}
					break;

				case Etape_1_Calibrage:
					if(fin_de_course_process==1)
					{
						etat_calibrage=Etape_2_Calibrage;
						recu_mae = command( 1, ID_MOT_2, CMD_RUN_BACKWARD, 0x1800, &read_value_mae);
						HAL_Delay(30);
					}
					break;

				case Etape_2_Calibrage:
					if(fin_de_course_home==1)
					{
						etat_calibrage=Etape_3_Calibrage;
						recu_mae = command( 1, ID_MOT_2, CMD_SOFT_STOP, 0x00, &read_value_mae);
						HAL_Delay(1500);
						recu_mae = command( 1, ID_MOT_2, CMD_GOTO, 0x1EE * DIVISEUR_STEP_1, &read_value_mae);//AVANCE UN PEU
						disponible=0;
						HAL_Delay(500);
						fin_de_course_home=0;
					}
					break;

				case Etape_3_Calibrage:

					if(disponible==1)
					{
						recu_mae = command( 1, ID_MOT_2,  CMD_RUN_BACKWARD, 0x1000, &read_value_mae);//RECULE DOUCEMENT
						HAL_Delay(30);
						if(fin_de_course_home==1)
						{
							etat_calibrage=Fin_Calibrage;
							recu_mae = command( 1, ID_MOT_2, CMD_SOFT_STOP, 0x00, &read_value_mae);
							HAL_Delay(500);
							fin_de_course_home=0;
							fin_procedure_calibrage=1;

							frame_display_led(frame,&size, 0x0C, 0); // LED EN COURS
							HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
							HAL_Delay(100);

							frame_display_led(frame,&size, 0x0D, 1); // LED FIN CALIBRAGE
							HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
							HAL_Delay(100);
							HAL_Delay(10);

						}
					}


					break;

				case Fin_Calibrage:

					if (fin_procedure_calibrage==1)
					{
						start_calibrage=0;
						*etat_mae=etatCalibrageLongueur;
					}
					break;
				}
			}
			break;


		case etatTempsPrechauffage:
			nform=10;//forme ecran
			if (type == BUTTON)
			{
				switch(nb)
				{
					case 44:
						//HOME
						HAL_Delay(10);
						selection_position_prechauffage=0;

						frame_display_led(frame,&size, 0x00, 1); // LED 0
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

						HAL_Delay(50);//Pour être sur que l'information soit transmise (sinon bug led)

						frame_display_led(frame,&size, 0x01, 0); // LED 1
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

						HAL_Delay(50);

						frame_display_led(frame,&size, 0x02, 0); // LED 2
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

						break;

					case 45:
						//MILIEU
						HAL_Delay(10);
						selection_position_prechauffage=1;
						frame_display_led(frame,&size, 0x01, 1); // LED 1
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);
						frame_display_led(frame,&size, 0x00, 0); // LED 0
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);
						frame_display_led(frame,&size, 0x02, 0); // LED 2
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

						break;

					case 46:
						//ENTREE FOUR
						HAL_Delay(10);
						selection_position_prechauffage=2;
						frame_display_led(frame,&size, 0x02, 1); // LED 2
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);
						frame_display_led(frame,&size, 0x00, 0); // LED 0
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);
						HAL_Delay(50);
						frame_display_led(frame,&size, 0x01, 0); // LED 1
						HAL_UART_Transmit(&huart1, (uint8_t *) frame, (u_int16_t)size, 100);

						break;

					case 40:
						//+1 min
						HAL_Delay(10);
						plus_1min_prechauffage();
						break;

					case 41:
						//-1 min
						HAL_Delay(10);
						moins_1min_prechauffage();
						break;

					case 38:
						//+10 min
						HAL_Delay(10);
						plus_10min_prechauffage();
						break;

					case 39:
						//-10 min
						HAL_Delay(10);
						moins_10min_prechauffage();
						break;

					case 42:
						//+1h
						HAL_Delay(10);
						nform=10;//forme ecran
						HAL_Delay(10);
						plus_1h_prechauffage();
						break;

					case 43:
						//-1h
						HAL_Delay(10);
						nform=10;//forme ecran
						HAL_Delay(10);
						moins_1h_prechauffage();
						break;
				}
			}
			break;

		case etatPositionsPredefinies:
			break;

		/*default :

			if(fin_de_course_home==1)
			{
				pos_init=1;//valide que le moteur est bien au HOME et permet de dévéroullier la mae pour passer dans l'état accueil
			}*/

	}

}
















