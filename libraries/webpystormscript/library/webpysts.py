#!/usr/bin/python
import web
import sys
import os

os.system("touch commands.txt")
command=open("commands.txt", 'r')

    
if (sys.argv[2]=="run") or (sys.argv[2]=="gaerun"):

    cmds=str(command.read()).split("\n")
    print "Welcome to STS web.py, please delete the commands.txt file after run"

    urls=(
        "/", "index"
    )
    app=web.application(urls,globals())

    for x in range(0,len(cmds)):
        if cmds[x]=="render":
            render=web.template.render(cmds[x+1])
        if cmds[x]=="port":
            prt=int(cmds[x+1])
        if cmds[x]=="addr":
            addr=cmds[x+1]

    class index:
        def GET(self):
            if "render" in cmds:
                return render.index()
            else:
                for x in range(0,len(cmds)-1):
                    if cmds[x]=="message":
                        return cmds[x+1]
                        

    if (sys.argv[2]=="run"):
        if __name__=="__main__":
            web.httpserver.runsimple(app.wsgifunc(), (addr, prt))
    else:
        app=app.gaerun()

if sys.argv[2]=="addr":
    with open("commands.txt", 'a') as commands:
        commands.write("addr\n"+sys.argv[3]+"\n")

if sys.argv[2]=="port":
    with open("commands.txt", 'a') as commands:
        commands.write("port\n"+sys.argv[3]+"\n")

if sys.argv[2]=="render":
    with open("commands.txt", 'a') as commands:
        commands.write("render\n"+sys.argv[3]+"\n")

if sys.argv[2]=="message":
    with open("commands.txt", 'a') as commands:
        commands.write("message\n"+sys.argv[3]+"\n")