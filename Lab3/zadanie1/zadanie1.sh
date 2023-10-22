 #!/bin/bash

#	-f do full format listing 
#	-l long format
#	-u userlist select by effective user ID or name
#		example: ps -u tomasz,root
#	
#	-p select processes with from given process id (PID) list
#
#
#

ps -fp $(pgrep sshd)
ps -C sshd 
