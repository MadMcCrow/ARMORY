:: !/usr/bin/git
::
:: src/build.bat : 
::             how to build with windows
::
:: Copyright © Noé Perard-Gayot 2023.
:: Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php
@CD ../src
@RD /S /Q godot-cpp
@git clone https://github.com/godotengine/godot-cpp --depth 1 -q
@DEL /Q "godot-cpp/.git"
@CD armory
@scons
@CP bin/* ../armory/bin/win64