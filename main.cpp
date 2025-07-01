#include <fstream>

int main() {

    // Image

    const int image_width = 256;
    const int image_height = 256;

    // Render

    std::ofstream ImageFile("image.ppm");

    ImageFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++) {
        for (int j = 0; j < image_width; j++) {


            int r = 255 * (float(j) / image_width);
            int g = 255 * (float(i) / image_width);
            int b = 0.0;


            ImageFile << r << ' ' << g << ' ' << b << '\n';

        }
    }

    ImageFile.close();

}
