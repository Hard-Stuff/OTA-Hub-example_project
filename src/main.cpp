#include <Arduino.h>

// OTA Hub via GitHub
#include <OTA-Hub.hpp>
#include <OTA-Hub/FOTA-providers/github.hpp>
#include <WiFiClientSecure.h>

WiFiClientSecure wifi_client;
OTAHub::FOTA::GithubProvider provider(
    "Hard-Stuff",
    "OTA-Hub-examples");

void setup()
{
  // Initialise our board
  Serial.begin(115200);
  Serial.println("Started...");

  WiFi.begin("Hard-Stuff.com", "your password");
  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("WiFi failure");
    ESP.restart();
  }

  // Initialise OTA
  wifi_client.setCACert(OTAHub::certs::GITHUB_CA); // Set the api.github.com SSL cert on the WiFiSecure modem
  OTAHub::FOTA::init(wifi_client, provider);

  // Check OTA for updates
  OTAHub::FOTA::UpdateObject details = OTAHub::FOTA::isUpdateAvailable();
  details.print();

  Serial.println(OTAHub::FOTA::ota_provider->FIRMWARE_WAS_BUILT_ON_PROVIDER
                     ? "This was built on Git."
                     : "This was built locally.");

  if (OTAHub::FOTA::NO_UPDATE != details.condition)
  {
    Serial.println("An update is available!");
    // Perform OTA update - will auto restart
    if (OTAHub::FOTA::performUpdate(&details) != OTAHub::FOTA::SUCCESS)
    {
      // Something is wrong...
    }
  }
  else
  {
    Serial.println("No new update available. Continuing...");
  }
  Serial.print("Loop");
}

void loop()
{
  delay(5000);
  Serial.print("edy loop");
}