import java.util.*;

public class RechercheComplexe {
    private final ArrayList<Map<String, Integer>> arrayMapsResRaw = new ArrayList<>();
    private final ArrayList<List<ScorePath>> arrayOfArrayOfScorePath = new ArrayList<>();
    int nbTexteMax;
    Map<String, Double> mapTotalScore = new HashMap<>();
    private String historiqueRecherche;
    private String historiqueResultats;
    private ArrayList<Map<String, Integer>> arrayMapsRes = new ArrayList<>();
    private ArrayList<ArrayList<String>> arrayOfArrayOfTextesString = new ArrayList<>();
    private ArrayList<List<ScorePath>> arrayOfArrayOfResultats = new ArrayList<>();
    private String[] tabRecherche;
    private int nbNegatif;
    private int nbPositif;
    wrapperIvyPfr wrapperIvy = new wrapperIvyPfr();

    private RechercheComplexe() {

    }

    public static RechercheComplexe getInstance() {
        return RechercheComplexeHolder.instance;
    }

    public static Map<String, Integer> negateMapValues(Map<String, Integer> originalMap) {
        Map<String, Integer> negatedMap = new HashMap<String, Integer>();
        for (Map.Entry<String, Integer> entry : originalMap.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            negatedMap.put(key, -value);
        }
        return negatedMap;
    }

    public static ArrayList<Map<String, Integer>> generateMaps(ArrayList<List<ScorePath>> scorePaths) {
        ArrayList<Map<String, Integer>> maps = new ArrayList<>();

        for (List<ScorePath> paths : scorePaths) {
            Map<String, Integer> map = new HashMap<>();

            for (ScorePath path : paths) {
                map.put(path.getPath(), path.getScore());
            }
            maps.add(map);
        }
        return maps;
    }

    public static Map<String, Double> trieMapOrdreDecroiss(Map<String, Double> map) {
        List<Map.Entry<String, Double>> list = new ArrayList<>(map.entrySet());

        list.sort((o1, o2) -> o2.getValue().compareTo(o1.getValue()));

        Map<String, Double> sortedMap = new LinkedHashMap<>();
        for (Map.Entry<String, Double> entry : list) {
            sortedMap.put(entry.getKey(), entry.getValue());
        }
        return sortedMap;
    }

    private static Map<String, Integer> convertirListEnMap(String liste) {
        Map<String, Integer> map = new HashMap<>();
        String[] textes = liste.split(";");
        for (String texte : textes) {
            String[] elements = texte.split("=");
            String nom = elements[0].trim();
            int valeur = Integer.parseInt(elements[1].trim());
            map.put(nom, valeur);
        }
        return map;
    }

    public static ArrayList<ArrayList<String>> convertirListes(String[] tableaux) {
        ArrayList<ArrayList<String>> resultats = new ArrayList<>();
        for (String tableau : tableaux) {
            String[] elements = tableau.split(";");
            ArrayList<String> liste = new ArrayList<>(Arrays.asList(elements));
            resultats.add(liste);
        }
        return resultats;
    }

    public Map<String, Double> recherche(String recherche) {
        System.out.println(recherche);
        historiqueRecherche = recherche.trim();
        tabRecherche = recherche.trim().split(" ");
        for (String str : tabRecherche) {
            str = str.substring(1);
            System.out.println(str);
            Motor motor1=new Motor(1,"main.out",".config1");
            wrapperIvy.addMotor(motor1);
            arrayOfArrayOfScorePath.add(wrapperIvy.sendRequete(motor1,wrapperIvyPfr.ADDR_TEXTE_MOTCLE,str,5));
        }

        String resultats = "Texte UV=15;Texte XY=6;Texte KL=2;89=1;45=4:" +
                "Texte XY=12;Texte KL=7;Texte UV=3;45=1:" +
                "Texte KL=11;Texte 21=4;Texte UV=1";
        String[] resultat = resultats.split(":");


        for (String s : resultat) {
            arrayMapsResRaw.add(convertirListEnMap(s));
        }

        nbTexteMax = maximumSizeMapInArrayList(arrayMapsResRaw).size();

        arrayOfArrayOfTextesString = convertirListes(resultat);

        arrayOfArrayOfResultats = listToArrayOfArrays(resultat);
        arrayMapsRes = generateMaps(arrayOfArrayOfScorePath);

        int i = 0;
        for (String s : tabRecherche) {
            if (s.charAt(0) == '-') {
                arrayMapsRes.set(i, negateMapValues(arrayMapsRes.get(i)));
                nbNegatif++;
            } else nbPositif++;
            i++;
        }


        mapTotalScore = calculateTotalScores(arrayMapsRes);

        Map<String, Double> sortedMap;
        sortedMap = trieMapOrdreDecroiss(mapTotalScore);

        historiqueResultats = sortedMap.toString();

        return sortedMap;
    }

    public Map<String, Double> calculateTotalScores(ArrayList<Map<String, Integer>> maps) {
        Map<String, Double> totalScores = new HashMap<>();
        for (Map<String, Integer> map : maps) {
            for (Map.Entry<String, Integer> entry : map.entrySet()) {
                int i = 0;
                double score = 0;
                if (tabRecherche[i].charAt(0) == '+') {
                    score = (double) entry.getValue() / nbPositif;
                } else if (tabRecherche[i].charAt(0) == '-') {
                    score = (double) entry.getValue() / nbNegatif;
                }
                if (totalScores.containsKey(entry.getKey())) {
                    score += totalScores.get(entry.getKey());
                }

                totalScores.put(entry.getKey(), score);
            }
        }
        return totalScores;
    }

    public String getHistorique() {
        return "\n" + getInstance().DateDuJour() + "\nRecherche = " + historiqueRecherche + "\n" + "Résultats = " + historiqueResultats + "\n\n";
    }

    private ArrayList<List<ScorePath>> listToArrayOfArrays(String[] tabRecherche) {

        for (int i = 0; i < tabRecherche.length; i++) {
            arrayOfArrayOfResultats.add(new ArrayList<>());
        }
        for (List<String> list : arrayOfArrayOfTextesString) {
            while (list.size() != nbTexteMax) {
                list.add("null");
            }
        }
        for (int i = 0; i < tabRecherche.length; i++) {
            for (int j = 0; j < nbTexteMax; j++) {
                if (!Objects.equals(arrayOfArrayOfTextesString.get(i).get(j), "null")) {
                    arrayOfArrayOfResultats.get(i).add(new ScorePath(Integer.parseInt(arrayOfArrayOfTextesString.get(i).get(j).split("=")[1]),
                            arrayOfArrayOfTextesString.get(i).get(j).split("=")[0]));
                }
            }
        }
        return arrayOfArrayOfResultats;
    }

    public String DateDuJour() {

        Calendar calendar = Calendar.getInstance();
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH) + 1; // ajout de 1 car janvier = 0
        int day = calendar.get(Calendar.DAY_OF_MONTH);
        int hour = calendar.get(Calendar.HOUR_OF_DAY);
        int minute = calendar.get(Calendar.MINUTE);

        return year + "-" + month + "-" + day + " " + hour + ":" + minute;

    }

    public Map<String, Integer> maximumSizeMapInArrayList(ArrayList<Map<String, Integer>> res) {
        int maxSize = Integer.MIN_VALUE;
        Map<String, Integer> maxSizeMap = null;

        for (Map<String, Integer> map : res) {
            if (map.size() > maxSize) {
                maxSize = map.size();
                maxSizeMap = map;
            }
        }
        return maxSizeMap;
    }

    private static class RechercheComplexeHolder {
        private static final RechercheComplexe instance = new RechercheComplexe();
    }


}



