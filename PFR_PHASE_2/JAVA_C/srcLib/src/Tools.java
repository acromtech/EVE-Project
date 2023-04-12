import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

public class Tools {
    public static Map<String, Integer> negateMapValues(Map<String, Integer> originalMap) {
        Map<String, Integer> negatedMap = new HashMap<String, Integer>();
        for (Map.Entry<String, Integer> entry : originalMap.entrySet()) {
            String key = entry.getKey();
            Integer value = entry.getValue();
            negatedMap.put(key, -value);
        }
        return negatedMap;
    }

    /**
     * Génère une ArrayList<Map<String, Integer>> a partir d'une ArrayList<List<ScorePath>>
     * @param scorePaths
     * @return
     */
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

    /**
     * Trie une Map par ordre décroissant de Score
     * @param map
     * @return
     */
    public static List<ScorePath> trieMapOrdreDecroiss(Map<String, Double> map) {
        List<ScorePath> paths = new ArrayList<>();
        for(String path : map.keySet()) {
            paths.add(new ScorePath((int)map.get(path).doubleValue(), path));
        }

        Collections.sort(paths, new Comparator<ScorePath>() {
            @Override
            public int compare(ScorePath s1, ScorePath s2) {
                return Integer.compare(s2.getScore(), s1.getScore());
            }
        });

        return paths;
    }

    /**
     * Retourne la date du jour au format : year + "-" + month + "-" + day + " " + hour + ":" + minute
     * @return
     */
    public static String DateDuJour() {
        Calendar calendar = Calendar.getInstance();
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH) + 1; // ajout de 1 car janvier = 0
        int day = calendar.get(Calendar.DAY_OF_MONTH);
        int hour = calendar.get(Calendar.HOUR_OF_DAY);
        int minute = calendar.get(Calendar.MINUTE);

        return year + "-" + month + "-" + day + " " + hour + ":" + minute;
    }

    /**
     * Affiche tous les scores et les chemins de la liste sur la console
     * @param ScorePathList
     */
    public static void printScorePathList(List<ScorePath> ScorePathList){
        for (ScorePath scorePath : ScorePathList) {
            System.out.println("JAVA\tScore : " + scorePath.getScore() + " - Path : " + scorePath.getPath());
        }
    }

    public static void printStringDoubleMap(Map<String,Double> StringDoubleMap){
        for (Map.Entry<String, Double> entry : StringDoubleMap.entrySet()) {
            String key = entry.getKey();
            Double value = entry.getValue();
            System.out.println(key + " : " + value);
        }
    }
}
