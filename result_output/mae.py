dir="bfcs"
str="bfcs"
import os
import shutil
if os.path.exists(dir)==False:
    os.mkdir(dir)
def fplt():
    f=open(str+".plt","w")	
    f.write("set xlabel \"\\\\Huge{Number of missing values}\" offset 0,0\n"
            "set ylabel \"\\\\Huge{MAE}\" offset 0,0\n"
            "set logscale y\n"
            "set xrange [500:7500]\n"	
            "set yrange [0.02:1.0]\n"
            "set key below samplen 20 width 5.5 spacing 5.5 font \",10\" \n"
            "set grid\n"
            "set samples 1000\n"
            "plot \"GROUPLENSaverageMaeFmeasureAuc.txt\" using 1:2 title \"\\\\Huge{conv}\" w line linewidth 15 lc rgb \"grey60\",\"BFCSaverageMaeFmeasureAuc4.txt\" using 1:2 title \"\\\\Huge{4C}\" w line linewidth 15 dt (1,2) lc rgb \"black\",\"BFCSaverageMaeFmeasureAuc5.txt\" using 1:2 title \"\\\\Huge{5C}\" w line linewidth 15 lc rgb \"grey90\"\n"#,\"BFCSaverageMaeFmeasureAuc6.txt\" using 1:2 title \"\\\\Huge{6C}\" w lines dt 3 linewidth 15 lc rgb \"black\"
            "set ticslevel 0\n"
            "set terminal epslatex color 12\n"
            "set output \""+dir+"/"+str+".eps\"\n"
            "replot"
        )
    f.close()
fplt()
os.system("gnuplot "+str+".plt")
tex2=dir+"/"+str+".tex"
os.system("sed -i -e \"1i \\\\\\\\\\\\documentclass[a4paper,12pt]{article}\" "+tex2)
os.system("sed -i -e \"2i \\\\\\\\\\\\usepackage{graphicx}\" "+tex2)
os.system("sed -i -e \"3i \\\\\\\\\\\\pagestyle{empty}\" "+tex2)
os.system("sed -i -e \"4i \\\\\\\\\\\\begin{document}\" "+tex2)
os.system("sed -i -e \"5i \\\\\\\\\\\\begin{figure}\" "+tex2)
os.system("sed -i -e 's/\\$0\\$/\\\\\\Huge{$0$}/' "+tex2)
os.system("sed -i -e 's/\\$1\\$/\\\\\\Huge{$1$}/' "+tex2)
os.system("sed -i -e 's/\\$0.1\\$/\\\\\\Huge{$0.1$}/' "+tex2)
os.system("sed -i -e 's/\\$500\\$/\\\\\\Huge{$500$}/' "+tex2)
os.system("sed -i -e 's/\\$1000\\$/\\\\\\Huge{$1000$}/' "+tex2)
os.system("sed -i -e 's/\\$3000\\$/\\\\\\Huge{$3000$}/' "+tex2)
os.system("sed -i -e 's/\\$5000\\$/\\\\\\Huge{$5000$}/' "+tex2)
os.system("sed -i -e 's/\\$7000\\$/\\\\\\Huge{$7000$}/' "+tex2)
os.system("sed -i -e 's/192/160/' "+tex2)
#os.system("sed -i -e 's/183/0/' "+tex2)
#os.system("sed -i -e 's/423/330/g' "+tex2)
#os.system("sed -i -e 's/648/690/g' "+tex2)
os.system("sed -i -e \"$ a \\\\\\\\\\\\end{figure}\" "+tex2)
os.system("sed -i -e \"$ a \\\\\\\\\\\\end{document}\" "+tex2)
os.system("sed -i -e \"95,96d\" "+tex2)
os.system("sed -i -e \"97,98d\" "+tex2)
os.system("sed -i -e \"99,100d\" "+tex2)
os.system("platex -output-directory="+dir+" "+tex2)
os.system("dvips -o "+dir+"/"+str+".ps "+dir+"/"+str)
os.system("ps2epsi "+dir+"/"+str+".ps "+dir+"/"+str+".eps")
#os.system("mv -f "+dir+"/"+str+".eps "+"~/comm/FSS2016sample-LaTeX/"+dir)
