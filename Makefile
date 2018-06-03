CXX = g++
PKG_DEFAULT = `pkg-config gstreamer-1.0 gtk+-2.0 opencv --libs`
SOURCE = *.cpp
EXEC = Facetracker


default:
	$(CXX) $(SOURCE) -o $(EXEC) $(PKG_DEFAULT)

clean:
	rm -rf $(EXEC) *.o

new: clean
	make default




