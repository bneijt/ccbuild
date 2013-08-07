/*
  This file is part of ccbuild.
  Copyright (C) 2013  A. Bram Neijt <bneijt@gmail.com>

  ccbuild is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ccbuild is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ccbuild.  If not, see <http://www.gnu.org/licenses/>.
*/
/* An attempt to write a PNG file that can be read be the likes of
   Mozilla/IE/the GIMP.  It will only uses a very small portion of the
   available functionality of PNG.  All I want is to be able to create
   images.
*/

#include <string>
#include <png.h>
using namespace std;

class PNGImage {
	string filename;
	FILE* fp;

public:
	PNGImage() : fp(NULL) {}
	PNGImage(string _filename) : filename(_filename), fp(NULL) {}
	~PNGImage();

	bool isPNG(int bytesToCheck);

private:

	bool openFile();
};


PNGImage::~PNGImage() {
	if (fp!=NULL) fclose(fp);
}


bool PNGImage::openFile() {
	if (fp!=NULL) {
		printf("file already opened\n");
		return false;	// can't open an already opened file
	}

	fp = fopen(filename.c_str(), "rb");
	if (!fp) {
		printf("couldn't open file %s\n", filename.c_str());
		return false;			// couldn't open file
	}

	printf("opened file %s\n", filename.c_str());

	return true;
}


bool PNGImage::isPNG(int bytesToCheck = 8) {
	if (fp==NULL) {
		if (openFile() == false) return false;
	}

	if (bytesToCheck > 8) {
		bytesToCheck=8;
		printf("bytesToCheck set to 8.  It cannot be more than 8.\n");
	}
	else if (bytesToCheck < 1) {
		bytesToCheck=1;
		printf("bytesToCheck set to 1.  It cannot be less than 1.\n");
	}

	// todo: check that fp is at start of file.

	char header[8];	// 8 is than maximum size that can be checked.

	int retValue = fread(header, 1, bytesToCheck, fp);
	if (retValue != bytesToCheck) {
		printf("couldn't read %d bytes from file.\n", bytesToCheck);
	}

	// use library to check if it's a valid PNG file
	bool valid;
	valid = ( png_sig_cmp((png_byte*)header, 0, bytesToCheck) == 0);

	return valid;
}


int main(int argc, char* argv[]) {
	// open file depending on argument passed from command line
	string filename("pngtest.png");
	if (argc==2) filename.assign(argv[1]);

	PNGImage image(filename);
	if (image.isPNG()) printf("file is PNG image\n");
	else printf("file is not PNG image\n");

	printf("finished.\n");

	return 0;	// success
}
