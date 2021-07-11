Analyze: peakAnalysis.o
	g++ -I `root-config --incdir` -o Analyze peakAnalysis.o `root-config --libs`
peakAnalysis.o: peakAnalysis.cpp
	g++ -c -I `root-config --incdir` peakAnalysis.cpp
clean:
	rm *.o
