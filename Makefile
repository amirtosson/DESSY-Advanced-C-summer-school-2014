EXE = sample-app
OBJ = event.o flavor.o histogram.o lorentzvector.o main.o mc-integral.o me-pp-to-llbar.o rambo.o school-rng.o threevector.o 

CXX      = c++
CXXFLAGS = -Wall -std=c++0x
LDFLAGS  =

all: $(EXE)

.PHONY: clean

clean:
	rm -f $(EXE) $(OBJ)

$(EXE): $(OBJ)
	$(CXX) -o $@ $(LDFLAGS) $+

# --- object dependencies ---

event.o: event.cc event.h flavor.h lorentzvector.h threevector.h \
 school-rng.h rambo.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

flavor.o: flavor.cc flavor.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

histogram.o: histogram.cc histogram.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lorentzvector.o: lorentzvector.cc lorentzvector.h threevector.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cc mc-integral.h event.h flavor.h lorentzvector.h \
 threevector.h matrix-element.h qcd-pdf.h analyser.h histogram.h \
 me-pp-to-llbar.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

mc-integral.o: mc-integral.cc mc-integral.h event.h flavor.h \
 lorentzvector.h threevector.h matrix-element.h qcd-pdf.h analyser.h \
 histogram.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

me-pp-to-llbar.o: me-pp-to-llbar.cc me-pp-to-llbar.h matrix-element.h \
 event.h flavor.h lorentzvector.h threevector.h school-rng.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

rambo.o: rambo.cc rambo.h event.h flavor.h lorentzvector.h threevector.h \
 school-rng.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

school-rng.o: school-rng.cc school-rng.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

threevector.o: threevector.cc threevector.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

