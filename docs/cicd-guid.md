# Setting up your CI CD

- OTA relies on 3 things working:
  1. **Source code** - A place to store and develop your applications e.g. GitHub or GitLab, here it is our Git repo.
  2. **Build engine** - A way to build firmware into `firmware.bin` files. In at-scale environments this is your pipelines (e.g. AWS EC2), here it is our Git repo.
  3. **Version checker** - A place to check if new firmware exists. In at-scale environments that is your Fleet Manager (e.g. AWS IoT Core), here it is our Git repo.
  4. **Build store** - A place to store built `firmware` files cleanly. In at-scale environments this is your cloud bucket (e.g. AWS S3), here it is our Git repo.

- You may notice already what's super cool about OTA Hub on GitHub/GitLab:
  - One place for your code, for your firmware building, for your checking endpoints, and for your firmware release hosting.
- This is obviously less flexible and scalable than professional at-scale custom environments, like AWS.
- But it is far, far easier to get started and far more suitable for hobbyists and prototypes. (and again, it's free!)

## CICD solves "thing 2" above, using GitHub/GitLab as our Build Engine

### General operation

_Applies to both GitHub and GitLab_

- Create a "Release" using GitHub or GitLab ([how do I create a release?](https://docs.github.com/en/repositories/releasing-projects-on-github/managing-releases-in-a-repository#creating-a-release)) - make sure to **create a new tag**
- Let GitHub/GitLab CI CD build your firmware into the different environments.
  - i.e. if you have multiple `platformio` environments, you get multiple firmware files.

**Example code**

- You can simply use this project template which includes:
  - [.github/workflows/](.github/workflows/) for GitHub, which features `deploy.yml` for releases as defined above, and `pr_to_main.yml` for pull requests to main (optional, this just checks everything built correctly).
  - [.gitlab-ci.yml](.gitlab-ci.yml) for GitLab, which only does the releases deployment as defined above.

### Ignoring environments

- You can put `# -- CICD IGNORE BUILD --` before all the builds you want to ignore, CI CD will skip them - this is beneficial for local-only environments e.g. setting privaate tokens, testing locally, etc.
  ```
  [env:default]

  [env:ENV_2]
  build_flags = 
    ${env:default_dev.build_flags}
    -D SOME_OTHER_DEF="Batman!"

  # -- CICD IGNORE BUILD --

  [env:ENV_3] # This will not be released, e.g. if used only for local testing
  build_flags = 
    ${env:default_dev.build_flags}
    -D SOME_OTHER_DEF="LOCAL Batman!"
  ```

## Useful tool: Serial Flashing in the browser (i.e. without VSCode)

The releases created by our CI CD here also work very nicely with Hard Stuff's flashing tool [flash.hard-stuff.com](https://flash.hard-stuff.com), which enables you to flash new firmware based on GitHub/GitLab releases over USB Serial in the browser, without needing to download VSCode etc. Very useful for quick flashes or getting clients/teammates (who are not firmware engineers) new versions.