# OTA-Hub | ESP32 DFU Over the Air directly from GitHub

An example on getting firmware updates to your ESP32 projects directly from GitHub releases (i.e. OTA updates, all for free!).

[![GitHub version](https://img.shields.io/github/v/release/Hard-Stuff/OTA-Hub-examples-github_project.svg)](https://github.com/Hard-Stuff/OTA-Hub-examples-github_project/releases/latest)
[![GitHub wiki](https://img.shields.io/badge/Wiki-available-brightgreen.svg)](https://github.com/Hard-Stuff/OTA-Hub-examples-github_project/wiki)
[![GitHub stars](https://img.shields.io/github/stars/Hard-Stuff/OTA-Hub-examples-github_project.svg)](https://github.com/Hard-Stuff/OTA-Hub-examples-github_project/stargazers)
![License](https://img.shields.io/badge/license-MIT-blue.svg)

**<img src="https://raw.githubusercontent.com/tabler/tabler-icons/fe8d99667fd830142804cb166e1dbb8e97db5e83/icons/outline/brand-gitlab.svg" width="24"/> This repo serves as an example for GitHub**
**<img src="https://raw.githubusercontent.com/tabler/tabler-icons/fe8d99667fd830142804cb166e1dbb8e97db5e83/icons/outline/brand-github.svg" width="24"/> and for GitLab!**

**OTA Hub** is designed to do one thing, and one thing only:

    Deliver Over-the-Air updates onto your ESP32/embedded devices directly from your code releases in an obvious, clean, light-weight way.

**OTA Hub** is the open-source solution to enable building and hosting your firmware updates on Git (Hub or Lab) and accessing them simply on your ESP devices. This repo is the setup guide, and [the device client is available on the PlatformIO Registry](https://registry.platformio.org/libraries/hard-stuff/OTA-Hub-device_client) - there is also a more involved project example showing off even cooler features here.
<!-- TODO Matt, show off the project example! -->

**OTA Hub Cloud** _(coming soon)_ is a cloud software that builds on that by enabling per-device provisioning, and data endpoints to plug into your stack. Think AWS IoT Core but massively simplified - great for hobbyists, prototyping, and startups. OTA Hub Cloud comes in both free and paid tiers.

Find out more about this and our other open source projects and products at [ota-hub.com](ota-hub.com).

**What sucks about current systems**

- OTA has long been a sore point in hobbyist and early-stage prototyping because while AWS and Blynk etc. offer OTA solutions they all require so much set up, and crucially so much commitment that it hardly seems worth it.
- Combine that with the weird insistence on drag and dropping `.bin` files into file upload ports, or constantly replacing the file in a dedicated S3 bucket - it becomes a mess bound to go wrong (and impossible to actually trace to your code!).
- Oh, and for all that inconvenience you often have to pay, or are limited to only a handful of devices and throttled performance.

### The benefits of OTA-Hub

1. No-longer worry about drag-and-dropping `.bin` files into some fiddly UI.
2. Easily trace your code to your releases to your deployed firmware.
3. Not locked into any eco-systems you probably aren't using already (you're probably already using GitHub / GitLab).
4. Client-agnostic! Implement OTA Hub on-top of secure or insecure\* connections, on 4G, NB-IoT, or WiFi modules.
5. The DIY version is open-source, **completely free**, and GitHub/Lab hosting is also completely free!
6. i.e. free, clear, no-fuss, simple OTA - perfect for "just getting started".

_\* Note that our default examples are for SSL-enabled connections, as GitHub requires a secure connection. As this is open-source, you can of course use your own storage buckets APIs for insecure connections etc._

## Getting Started Steps

There are only two steps you need to consider for OTA updates from GitHub:

1. Set up the CI/CD (see [the CI CD guide](./docs/cicd-guide.md)) on your GitHub/Gitlab repo to automatically build the firmware on new releases.
    **<img src="https://raw.githubusercontent.com/tabler/tabler-icons/fe8d99667fd830142804cb166e1dbb8e97db5e83/icons/outline/brand-gitlab.svg" width="24"/> For GitHub**<br/>
    This is as easy as copying the [.github/workflows/](.github/workflows/) folder into your PlatformIO base directory (like in this example), or even just fork this repo! Then, build new releases as normal. <br /> 
    <img src="./docs/media/GitHub_releases.png" width="400px"/>
   
   **<img src="https://raw.githubusercontent.com/tabler/tabler-icons/fe8d99667fd830142804cb166e1dbb8e97db5e83/icons/outline/brand-gitlab.svg" width="24"/> and for GitLab**<br />
    This is as easy as copying the [.gitlab-ci.yml](.gitlab-ci.yml) file into your PlatformIO base directory (like in this example), or even just fork this repo! Then, build new releases as normal.

2. Include the [OTA-Hub esp client library](https://registry.platformio.org/libraries/hard-stuff/OTA-Hub-device_client) and example code you'll find in [src/main.cpp](src/main.cpp). Note the `#define`s, and the inclusion of `OTA::isUpdateAvailable()`, `OTA::performUpdate(..)`, and `OTA::followRedirect(..)`. <br /> <br />
   <img src="./docs/media/logs.png" width="400px"/>

   That's it!

### Platformio Dependencies

- [hard-stuff/OTA-Hub-diy-device_client](https://registry.platformio.org/libraries/hard-stuff/OTA-Hub-device_client)

## Further reading

- To avoid duplication, there is more content on how to set up GitHub, GitLab, custom providers, and further examples [github.com/Hard-Stuff/OTA-Hub-device_client](https://github.com/Hard-Stuff/OTA-Hub-device_client).

## Compatibility

This library has been tested on the ESP32S3 with both the internal WiFi functionality and a [SIMCOM SIM7600G](https://github.com/Hard-Stuff/TinyGSM), both with HTTP and HTTPS connections, both with GitHub and GitLab, and both on public and private repositories.

## Contribution
We're looking for people to work with us further on this - you can get started with issue reports or merge rquests, or you can contact us at [ota-hub@hard-stuff.com](mailto:ota-hub@hard-stuff.com).

## Hard Stuff

Hard Stuff is a hardware prototyping agency and venture studio focussing on sustainability tech, based in London, UK.
Find out more at [hard-stuff.com](hard-stuff.com).

This library is written and provided open-source in the hope that you go on to build great things.
