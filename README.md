# OTA Hub (by Hard Stuff) - OTA directly from GitHub, Example

This example project gets you set up using OTA Hub with GitHub, ready for Over-The-Air updates driven directly from your GitHub repo's releases, all for free!

You can follow along 95% of it for GitLab, just look for the `GitLab` if you want that.

**OTA Hub** is designed to do one thing, and one thing only:

    Deliver Over-the-Air updates onto your ESP32/embedded devices directly from your code releases in an obvious, clean, light-weight way.

**Names**
- **OTA Hub** is a solution to enable building and hosting your firmware updates on Git (Hub or Lab) and accessing them simply on your ESP devices. That's this repo, and it's entirely open source.
- **OTA Hub Cloud** _(coming soon)_ is a cloud software that builds on that by enabling per-device provisioning, and data endpoints to plug into your stack. Think AWS IoT Core but massively simplified - great for hobbyists, prototyping, and startups. OTA Hub Cloud comes in both free and paid tiers.

**What sucks about current systems**

- OTA has long been a sore point in hobbyist and early-stage prototyping (e.g. startups), because while AWS and Blynk etc. offer OTA solutions, they all require so much set up, and crucially so much commitment that it hardly seems worth it for early builds.
- Combine that with the weird insistence on drag and dropping `.bin` files into file upload portals, or constantly replacing the file in a dedicated S3 bucket - it becomes a mess bound to go wrong (and impossible to actually trace).

### Benefits over alternatives

1. No-longer worry about drag-and-dropping `.bin` files into some fiddly UI.
2. Easily trace your code to your releases to your deployed firmware.
3. Not locked into any eco-systems you probably aren't using already (you're probably already using GitHub).
4. Client-agnostic! Implement OTA Hub on-top of secure or insecure\* connections, on 4G, NB-IoT, or WiFi modules.
5. The OTA Hub Device Client pio package is open-source, so OTA is **completely free**, and GitHub/GitLab firmware building and hosting is also completely free!

_\* Note that our default examples are for SSL-enabled connections, as GitHub requires a secure connection. As this is open-source, you can of course use your own storage buckets APIs for insecure connections etc._

## Steps

There are only two steps you need to consider for OTA updates from GitHub:

1. Set up the CI/CD (see [the CI CD guide](./CICD-guide.MD)) on your GitHub repo to automatically build the firmware on new releases. This is as easy as copying the [.github/workflows/](.github/workflows/) project into your PlatformIO base directory (like in this example). Then, build new releases as normal. <br /> <br />
   <img src="./media/GitHub_releases.png" width="400px"/>

2. Include the [OTA-Hub esp client library](https://registry.platformio.org/libraries/hard-stuff/OTA-Hub-device_client) and example code you'll find in [src/main.cpp](src/main.cpp). Note the `#define`s, and the inclusion of `OTA::isUpdateAvailable()`, `OTA::performUpdate(..)`, and `OTA::followRedirect(..)`. <br /> <br />
   <img src="./media/logs.png" width="400px"/>

That's it!

### Dependencies

-   [hard-stuff/OTA-Hub-device_client](https://registry.platformio.org/libraries/hard-stuff/OTA-Hub-device_client)

## Private repositories (you will need to make a Personal Access Token or Fine Grain Access Token)

OTA Hub DIY works with both your public and private repositories, pulling release files (that are automatically compiled) directly from GitHub. If using a private repository, we need a Personal (or Fine Grain) Access Token (PAT) to represent you so devices can access your secure account. [You can generate your GitHub PATs here](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens), or [for GitLab](https://docs.gitlab.com/user/profile/personal_access_tokens/).

- Then, once created, you can dump the token in a `.token` file and run: 
  ```powershell
  # windows
  $env:PLATFORMIO_BUILD_FLAGS = "-DOTAHUB_BEARER_TOKEN=\`"$((Get-Content .token -Raw).Trim())\`""
  ```
  ```bash
  # linux
  token=$(cat .token)
  export PLATFORMIO_BUILD_FLAGS="-DOTAHUB_BEARER_TOKEN=\\\"$token\\\""
  ```
  or you can run:
  ```powershell
  # windows
  $env:PLATFORMIO_BUILD_FLAGS='-DOTAHUB_BEARER_TOKEN=\"PUTYOURTOKENHERE\"';
  ```
  ```bash
  # linux
  export PLATFORMIO_BUILD_FLAGS='-DOTAHUB_BEARER_TOKEN=\"PUTYOURTOKENHERE\"'
  ```
  Then run `pio run -t upload` once **in that same terminal** to write the token into the firmware, whereby on boot this token is stored to NVS. You only need to write this once - all future builds should not need the token as we then retrieve it from NVS.

## Further reading

- To avoid duplication, there is more content on how to set up GitHub, GitLab, custom providers, and further examples [github.com/Hard-Stuff/OTA-Hub-device_client](https://github.com/Hard-Stuff/OTA-Hub-device_client).

## Compatibility

This library has been tested on the ESP32S3 with both the internal WiFi functionality and a [SIMCOM SIM7600G](https://github.com/Hard-Stuff/TinyGSM), both with HTTP and HTTPS connections, both with GitHub and GitLab, and both on public and private repositories.

We are looking for people to support us in testing more boards, other connectivity functionalities, and making **OTA Hub Pro** even more useful - please make [issues](https://github.com/Hard-Stuff/OTA-Hub-examples/issues) should you come across any!

### Flashing without VSCode

_Mentioning here only because it might be useful_

The releases created by our CI CD here also work very nicely with Hard Stuff's flashing tool [flash.hard-stuff.com](https://flash.hard-stuff.com), which enables you to flash new firmware based on GitHub/GitLab releases over USB Serial in the browser, without needing to download VSCode etc. Very useful for quick flashes or getting clients/teammates (who are not firmware engineers) new versions.

## Contribution
We're looking for people to work with us further on this - you can get started with issue reports or merge rquests, or you can contact us at [ota-hub@hard-stuff.com](mailto:ota-hub@hard-stuff.com).

## Hard Stuff

Hard Stuff is a hardware prototyping agency and venture studio focussing on sustainability tech, based in London, UK.
Find out more at [hard-stuff.com](hard-stuff.com).

This library is written and provided open-source in the hope that you go on to build great things.
