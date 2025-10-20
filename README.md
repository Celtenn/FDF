<!-- ====================================================== -->
<!--   🌌  FdF (Fil de Fer) — by Enes Kahraman, 42 Kocaeli   -->
<!-- ====================================================== -->

<p align="center">
  <img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=30&pause=1000&color=00C2FF&center=true&vCenter=true&width=600&lines=🧩+FdF+(Fil+de+Fer);3B+Tel+Kafes+Görselleştirici;C+ile+Grafik+Programlama;42+Kocaeli+Projesi" alt="Typing SVG" />
</p>

---

<p align="center">
  <img src="https://img.shields.io/badge/Dil-C-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Okul-42_Kocaeli-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Proje-FdF-lightgrey?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Durum-Tamamlandı-success?style=for-the-badge" />
</p>

---

## 🌐 Hakkında

**FdF (Fil de Fer)**, 42 okulu müfredatındaki **grafik tabanlı** bir C projesidir.  
Amaç, verilen bir yükseklik haritasını okuyarak 3B uzayda **tel kafes (wireframe)** biçiminde görselleştirmektir.  
Matematiksel dönüşümler ve grafik çizimleri ile 2B ekranda 3B bir görünüm oluşturur.

🧭 **Temel hedef:**  
Matematiksel mantığı görsel biçime çevirebilen bir grafik motoru oluşturmak.

<p align="center">
  <img src="https://github.com/Celtenn/fdf/assets/example_output.png" width="550" alt="FdF Preview">
</p>

---

## 🧠 Öğrenilen Temeller

| Konu | Açıklama |
|------|-----------|
| 🧮 **İzometrik Projeksiyon** | 3B noktaların 2B düzleme aktarılması. |
| ✏️ **Bresenham Algoritması** | Piksel tabanlı çizgi çizim algoritması. |
| 🔄 **Matris Dönüşümleri** | Döndürme, ölçekleme, çevirme işlemleri. |
| 💡 **MiniLibX** | 42’nin özel C grafik kütüphanesi. |

---

## ⚙️ Kurulum ve Çalıştırma

### 🔧 Gereksinimler
- macOS veya Linux  
- `gcc` veya `clang` derleyicisi  
- MiniLibX kütüphanesi (42 projeleri ile birlikte gelir)

### 📦 Kurulum

```bash
git clone https://github.com/Celtenn/fdf.git
cd fdf
make

./fdf maps/42.fdf

## 🧠 Öğrenilen Temeller

| Konu | Açıklama |
|------|-----------|
| 🧮 **İzometrik Projeksiyon** | 3B noktaların 2B düzleme aktarılması. |
| ✏️ **Bresenham Algoritması** | Piksel tabanlı çizgi çizim algoritması. |
| 🔄 **Matris Dönüşümleri** | Döndürme, ölçekleme, çevirme işlemleri. |
| 💡 **MiniLibX** | 42’nin özel C grafik kütüphanesi. |

---

## ⚙️ Kurulum ve Çalıştırma

### 🔧 Gereksinimler
- macOS veya Linux  
- `gcc` veya `clang` derleyicisi  
- MiniLibX kütüphanesi (42 projeleri ile birlikte gelir)

### 📦 Kurulum

git clone https://github.com/Celtenn/fdf.git
cd fdf
make
./fdf maps/42.fdf
⌨️ Klavye Kontrolleri
<p align="center">
Tuş	İşlev
⬆️ / ⬇️ / ⬅️ / ➡️	Görünümü hareket ettir
➕ / ➖	Yakınlaştır / Uzaklaştır
🌀 Q / E	Z ekseni etrafında döndür
♻️ R	Görünümü sıfırla
🚪 ESC	Programdan çık
</p>
fdf/
├── includes/
│   └── fdf.h
├── srcs/
│   ├── main.c
│   ├── parse_map.c
│   ├── draw.c
│   ├── projection.c
│   ├── hooks.c
│   └── utils.c
├── maps/
│   ├── 42.fdf
│   ├── mars.fdf
│   └── pyramid.fdf
├── Makefile
└── README.md
🧮 Matematiksel Arka Plan
🎲 İzometrik Projeksiyon

x′=(x−y)×cos(30°)
y′=(x+y)×sin(30°)−z

Bu dönüşüm, 3B uzayda bulunan noktaları 2B ekranda derinlik hissi vererek gösterir.

📈 Bresenham Algoritması

void draw_line(t_point a, t_point b)
{
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = (a.x < b.x) ? 1 : -1;
    int sy = (a.y < b.y) ? 1 : -1;
    int err = dx - dy;

    while (a.x != b.x || a.y != b.y)
    {
        put_pixel(a.x, a.y, color);
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; a.x += sx; }
        if (e2 < dx) { err += dx; a.y += sy; }
    }
}

🧰 Makefile Komutları
Komut	Açıklama
make ->	Programı derler
make clean	-> Ara dosyaları temizler
make fclean	-> Tüm derleme çıktısını siler
make re	-> Baştan derleme yapar

🧑‍💻 Yazar

Enes Kahraman
📍 42 Kocaeli
🔗 GitHub: Celtenn
