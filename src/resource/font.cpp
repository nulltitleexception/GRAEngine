#include "font.h"

#include "config.h"

#include <iostream>
#include <algorithm>

namespace GRAE {
FontData::FontData(std::string path, Resources *res) {
    File file(path + ".fdat");
    data = (int *) file.getBytes();
    maxSize = *((int *) data);
    num = *(((int *) data) + 1);
}

int FontData::getMaxSize() {
    return maxSize;
}

int FontData::getNum() {
    return num;
}

int *FontData::getPositions(int size) {
    return data + 4 + ((num + 1) * (size - 1) * 2);
}

int FontData::getTop(int size) {
    return *(data + 2 + ((num + 1) * (size - 1) * 2));
}

int FontData::getBottom(int size) {
    return *(data + 3 + ((num + 1) * (size - 1) * 2));
}

Font::Font(std::string path, Resources *res) {
    Config cfg(path + ".fnt", res);
    texture = res->get<Texture>(cfg.getString("texture"));
    shader = res->get<Shader>(cfg.getString("shader"));
    data = res->get<FontData>(cfg.getString("data"));
}

Text *Font::getText(std::string t, int size) {
    if (size > data->getMaxSize()) {
        ///throw? this is an error
        std::cout << "Font does not support size " << size << "!" << std::endl;
    }
    int ws = (int)(std::count(t.begin(), t.end(), ' ') + std::count(t.begin(), t.end(), '\t') +
             std::count(t.begin(), t.end(), '\n'));
    float *v = new float[(t.length() - ws) * 24];
    int xi = 0;
    int yi = 0;
    int i = 0;
    for (int j = 0; j < t.length(); j++) {
        int l = data->getPositions(size)[((int) t[j]) * 2];
        int r = data->getPositions(size)[(((int) t[j]) * 2) + 1];
        if (t[j] == ' ') {
            xi += (r - l);
            continue;
        } else if (t[j] == '\t') {
            xi += (r - l) * 4;
            continue;
        } else if (t[j] == '\n') {
            int t = data->getTop(size);
            int b = data->getBottom(size);
            xi = 0;
            yi += (b - t);
            continue;
        }
        float left = ((float) l) / texture->getWidth();
        float right = ((float) r) / texture->getWidth();
        float top = ((float) data->getTop(size)) / texture->getHeight();
        float bottom = ((float) data->getBottom(size)) / texture->getHeight();
        float x0 = xi;
        float y0 = yi;
        float x1 = xi + (r - l);
        float y1 = yi + (data->getBottom(size) - data->getTop(size));
        xi += (r - l);
        v[(i * 24)] = x0;
        v[(i * 24) + 1] = y0;
        v[(i * 24) + 2] = left;
        v[(i * 24) + 3] = top;
        v[(i * 24) + 4] = x1;
        v[(i * 24) + 5] = y0;
        v[(i * 24) + 6] = right;
        v[(i * 24) + 7] = top;
        v[(i * 24) + 8] = x1;
        v[(i * 24) + 9] = y1;
        v[(i * 24) + 10] = right;
        v[(i * 24) + 11] = bottom;
        v[(i * 24) + 12] = x0;
        v[(i * 24) + 13] = y0;
        v[(i * 24) + 14] = left;
        v[(i * 24) + 15] = top;
        v[(i * 24) + 16] = x1;
        v[(i * 24) + 17] = y1;
        v[(i * 24) + 18] = right;
        v[(i * 24) + 19] = bottom;
        v[(i * 24) + 20] = x0;
        v[(i * 24) + 21] = y1;
        v[(i * 24) + 22] = left;
        v[(i * 24) + 23] = bottom;
        i++;
    }

    return new Text(new Mesh2D(v, t.length() * 6), shader, texture);
}
}