Import("env")
import os

# access to global construction environment
#print env

# Dump construction environment (for debug purpose)
#print env.Dump()

# append extra flags to global build environment
# which later will be used to build:
# - project source code
# - frameworks
# - dependent libraries
cppdefines=[
  "PIO_FRAMEWORK_ARDUINO_ESPRESSIF_SDK22x_190703",
  "ESPEASY_MCVE_BUILD"
  # ,"NO_HTTP_UPDATER"
  # ,("WEBSERVER_RULES_DEBUG", "0")
]

if os.path.isfile('src/Custom.h'):
  cppdefines.append("USE_CUSTOM_H")
else:
  cppdefines.extend([
        "USES_P001",  # Switch
        "USE_SETTINGS_ARCHIVE"
  ])

env.Append(CPPDEFINES=cppdefines)

print(env['CPPDEFINES'])
