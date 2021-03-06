## Upgrade remote machines 
- Send packets to remote machines and try to upgrade the packet remotely.Troubleshooting why some of the machines are not updated.


**Prior to login for upgrade, We should configure [passwordless login using ssh public,pvt keys](/Operating_Systems/Linux/Administration/RemoteLogin/PasswordLess_Login.md)**

### 1. Approach-1  //Client-side script only
- **Logic**
  - *1.* Take username@IPAddresses in a file. Read this file line by line. call ssh and execute `yum upgrade` command on remote machine. Check the return status of `yum upgrade`.
```c
  amit@10.20.30.189
  test@10.118.161.22
```
- **Code**
  - [shebang](/Languages/ScriptingLanguages/Shell_Scripting/Bash/README.md), [$1](/Languages/ScriptingLanguages/Shell_Scripting/Bash/CommandLineArguments/%24.md), [$?](/Languages/ScriptingLanguages/Shell_Scripting/Bash/Exit_Status.md), [$@](/Languages/ScriptingLanguages/Shell_Scripting/Bash/CommandLineArguments/%24%40.md)
```bash
#!/usr/bin/env bash                       #shebang

sshRemote(){
  ssh $1 "sudo apt upgrade | grep 'success'"
  if [ $? == 0 ]                                  #Check return code
  then
    YUMSTATUS = 0
  else
    YUMSTATUS = 1
  fi
}

ReadFile() {              #Read every line from input file
  while IFS='' read -r ParsedLine
  do
    sshRemote ParsedLine
    if [ $YUMSTATUS == 0 ]
      echo "Upgrade Success"
    else
      echo "Upgrade Failed"
  done < "$1"
}

ReadLine $1
```

### 2. Approach-2    //2 sepearte scripts
- **Logic**
  - *1.* Create 2 seperate scripts. 
    - Client.sh: 1. scp work.sh to server   2. Execute work.sh on server    3. Get error or normal output of execute
- **Code**
  - **work.sh:** This will be placed on server and run.
```bash
#!/usr/bin/env bash                       #shebang
sudo apt upgrade -y 2>aptErrors.txt &>aptInstall.txt
```
  - **client.sh*
```bash
#!/usr/bin/env bash                       #shebang
SERVER=amit@ip-address
REMOTE_PATH=/home/server/work.sh

function fun(){
  echo  "Running: $@"
  "$@"
}

echo "---scp script to server--"
fun scp work.sh $SERVER:$REMOTE_PATH
echo "---running script to server--"
fun ssh $SERVER $REMOTE_PATH
echo "---Get errors from server--"
fun scp $SERVER $REMOTE_PATH  .
```
