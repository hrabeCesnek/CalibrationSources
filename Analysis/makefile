#Analyze: peakAnalysis.o
#	g++ -I `root-config --incdir` -o Analyze peakAnalysis.o `root-config --libs`
#peakAnalysis.o: peakAnalysis.cpp
#	g++ -c -I `root-config --incdir` peakAnalysis.cpp

FullAnalysis: AllFiles.o singlePulse.o
	g++ -I `root-config --incdir` -o  FullAnalysis AllFiles.o singlePulse.o `root-config --libs`
#AllFiles: AllFiles.o
#	g++ -I `root-config --incdir` -o AllFiles AllFiles.o `root-config --libs`
AllFiles.o: AllFiles.cpp
	g++ -c -I `root-config --incdir` AllFiles.cpp `root-config --incdir`
singlePulse.o: singlePulse.cpp
		g++ -c -Wall -I  `root-config --incdir` singlePulse.cpp `root-config --incdir`

clean:
	rm *.o
