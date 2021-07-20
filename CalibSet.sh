
#!/bin/bash
cd /home/dietpi/IntegrationSphere/otherRead/blikac/blikac/ && sudo python3 otherDiode.py
sleep 20
cd /home/dietpi/IntegrationSphere/ReadCP/linux-build-files/ && ./ps2000aCon Cal1
sleep 10
cd /home/dietpi/IntegrationSphere/otherRead/blikac/blikac/ && sudo python3 otherDiode2.py
sleep 20
cd /home/dietpi/IntegrationSphere/ReadCP/linux-build-files/ && ./ps2000aCon Cal2
sleep 10   
cd /home/dietpi/IntegrationSphere/otherRead/blikac/blikac/ && sudo python3 primaryDiode.py
