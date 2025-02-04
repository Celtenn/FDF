#include "fdf.h"

int animate_colors(t_data *data)
{
    static float t = 0.0f;

    // Renkleri güncelle
    data->start_color = create_rgb((int)(255 * sin(t)), (int)(255 * sin(t + 2)), (int)(255 * sin(t + 4)));
    data->end_color = create_rgb((int)(255 * sin(t + 1)), (int)(255 * sin(t + 3)), (int)(255 * sin(t + 5)));

    // Haritayı yeniden çiz
    mlx_clear_window(data->mlx, data->win);
    draw_map(data->map, data);

    // t değerini güncelle
    t += 0.01f;
   

    return (0);
}

void draw_line(t_point p0, t_point p1, t_data *data)
{
    int dx = abs(p1.x - p0.x);
    int dy = abs(p1.y - p0.y);
    int sx = (p0.x < p1.x) ? 1 : -1;
    int sy = (p0.y < p1.y) ? 1 : -1;
    int err = dx - dy;

    // Başlangıç ve bitiş renkleri
    unsigned int start_color = create_rgb(255, 0, 0); // Kırmızı
    unsigned int end_color = create_rgb(0, 0, 255);   // Mavi

    // Çizgi uzunluğu
    float line_length = sqrtf((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    float current_length = 0;

    while (1)
    {
        // Renk geçişi için t değeri
        float t = current_length / line_length;

        // Geçiş rengini hesapla
        unsigned int color = interpolate_color(start_color, end_color, t);

        // Piksel çiz
        draw_pixel(p0.x, p0.y, data, color);

        if (p0.x == p1.x && p0.y == p1.y)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            p0.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            p0.y += sy;
        }

        // Çizgi uzunluğunu güncelle
        current_length = sqrtf((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
    }
}

unsigned int create_rgb(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

unsigned int interpolate_color(unsigned int color1, unsigned int color2, float t)
{
    int r1 = (color1 >> 16) & 0xff;
    int g1 = (color1 >> 8) & 0xff;
    int b1 = color1 & 0xff;

    int r2 = (color2 >> 16) & 0xff;
    int g2 = (color2 >> 8) & 0xff;
    int b2 = color2 & 0xff;

    int r = r1 + (int)((r2 - r1) * t);
    int g = g1 + (int)((g2 - g1) * t);
    int b = b1 + (int)((b2 - b1) * t);

    return create_rgb(r, g, b);
}
