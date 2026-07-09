package com.example;
import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class App {
    public static void main(String[] args) {
        try {
            String country = "france";
            String result = Result.getBestChocolate(country);
            System.out.println("Results: " + result);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
            e.printStackTrace();
        }
    }
}



class Result {
    public static String getBestChocolate(String country) {
        try {
            HttpClient client = HttpClient.newHttpClient();
            Gson gson = new Gson();
            int page = 1;
            int totalPages = 1;
            int maxEnergy = Integer.MIN_VALUE;
            int minAvgPrice = Integer.MAX_VALUE;
            String bestBrand = "";
            String bestType = "";
            while (page <= totalPages) {
                String url = "https://jsonmock.hackerrank.com/api/chocolates?countryofOrigin=" + country + "&page="
                        + page;
                HttpRequest request = HttpRequest.newBuilder().uri(URI.create(url)).GET().build();
                HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
                JsonObject jsonObject = gson.fromJson(response.body(), JsonObject.class);
                totalPages = jsonObject.get("total_pages").getAsInt();
                JsonArray dataArray = jsonObject.getAsJsonArray("data");
                for (JsonElement element : dataArray) {
                    try {
                        JsonObject chocolate = element.getAsJsonObject();
                        String brand = chocolate.get("brand").getAsString();
                        String type = chocolate.get("type").getAsString();
                        JsonObject nutrition = chocolate.getAsJsonObject("nutritionalInformation");
                        int kcal = nutrition.get("kcal").getAsInt();
                        JsonArray weights = chocolate.getAsJsonArray("weights");
                        int totalWeight = 0;
                        for (JsonElement w : weights) {
                            totalWeight += w.getAsInt();
                        }
                        int avgWeight = totalWeight / weights.size();
                        int energy = (int) (kcal * 0.01 * avgWeight);
                        JsonArray prices = chocolate.getAsJsonArray("prices");
                        int totalPrice = 0;
                        for (JsonElement p : prices) {
                            totalPrice += p.getAsInt();
                        }
                        int avgPrice = totalPrice / prices.size();
                        if (energy > maxEnergy || (energy == maxEnergy && avgPrice < minAvgPrice)) {
                            maxEnergy = energy;
                            minAvgPrice = avgPrice;
                            bestBrand = brand;
                            bestType = type;
                        }
                    } catch (Exception e) {
                        System.out.println("Error processing item: " + e.getMessage());
                    }
                }
                page++;
            }
            return bestBrand + ":" + bestType;
        } catch (IOException | InterruptedException e) {
            Thread.currentThread().interrupt();
            return "";
        } catch (Exception e) {
            return "";
        }
    }
}