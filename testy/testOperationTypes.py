import os

def exitCodeForUnix(code):
    return os.WEXITSTATUS(code)

types = [1, 2.0, "'\"'3'\"'", True, None]
operations = ["+", "-", "*", "/", "//", "==", "!=", "<", "<=", ">", ">=", "and", "or"];
caseNum = 1
compiler = "../ifj"
interpret = "./interpret_by_adam_salih/interpret.py"
for operation in operations:
    for type1 in types:
        for type2 in types:
			expression = "res = " + str(type1) + " " + str(operation) + " " + str(type2)
			sourceName = "typeTest"+str(caseNum)+".src"
			outputName = "typeTest"+str(caseNum)+".ifjcode19"
			os.system("echo '"+expression+"\nprint(res)\n"+"' > "+sourceName)
			exitCode = exitCodeForUnix(os.system(compiler+" < "+sourceName+" > "+outputName))
			run = "[ x ]"
			if exitCode == 0:
			    run = "[ o ]"
			    exitCode = exitCodeForUnix(os.system(interpret+" --ifj "+outputName))
			print(run+" "+str(exitCode)+": "+expression+"")
			caseNum += 1
	print("==================================================")
