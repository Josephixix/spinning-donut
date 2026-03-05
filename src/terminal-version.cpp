#include <iostream>
#include <cmath>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    float A = 0, B = 0;

    const int width = 80;
    const int height = 22;

    float zBuffer[width * height];
    char buffer[width * height];

    cout << "\x1b[2J";

    while (true) {

        memset(buffer, ' ', width * height);
        memset(zBuffer, 0, sizeof(zBuffer));

        for (float j = 0; j < 6.28; j += 0.07) {
            for (float i = 0; i < 6.28; i += 0.02) {

                float sinA = sin(A), cosA = cos(A);
                float sinB = sin(B), cosB = cos(B);

                float sinJ = sin(j), cosJ = cos(j);
                float sinI = sin(i), cosI = cos(i);

                float h = cosJ + 2;

                float D = 1 / (sinI * h * sinA + sinJ * cosA + 5);

                float t = sinI * h * cosA - sinJ * sinA;

                int x = (int)(width / 2 + 30 * D * (cosI * h * cosB - t * sinB));
                int y = (int)(height / 2 + 15 * D * (cosI * h * sinB + t * cosB));

                int o = x + width * y;

                int N = (int)(8 * ((sinJ * sinA - sinI * cosJ * cosA) * cosB
                    - sinI * cosJ * sinA
                    - sinJ * cosA
                    - cosI * cosJ * sinB));

                if (y < height && y >= 0 && x >= 0 && x < width && D > zBuffer[o]) {
                    zBuffer[o] = D;
                    buffer[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        cout << "\x1b[H";

        for (int k = 0; k < width * height; k++) {
            cout << (k % width ? buffer[k] : '\n');
        }

        A += 0.04;
        B += 0.02;

        this_thread::sleep_for(chrono::milliseconds(30));
    }

    return 0;
}