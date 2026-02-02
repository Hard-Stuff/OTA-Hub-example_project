# Private repositories

OTA Hub DIY works with both your public and private repositories, pulling built firmware releases directly from GitHub and GitLab. If using a private repository, we need a Personal (or Fine Grain) Access Token (PAT) to represent you so devices can access your secure accoutn. [You can generate your PATs here](https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens).

- Then, once created, you can dump the token in a `.token` file and run _(example for **Windows**)_: 
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
  Then run `pio run -t upload` once **in that same terminal** to write the token into the firmware, whereby on boot this token is stored to NVS. All future builds should not need the token as we then retrieve it from NVS.