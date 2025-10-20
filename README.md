<h1 align="center">🧩 FdF — 3B Tel Kafes Görselleştirici</h1>

<p align="center">
  <img src="https://img.shields.io/badge/Dil-C-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Okul-42_Kocaeli-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Proje-FdF-lightgrey?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Durum-Tamamlandı-success?style=for-the-badge" />
</p>

<p align="center">
  <img src="https://github.com/Celtenn/fdf/assets/preview.gif" width="600" alt="FdF Önizleme">
</p>

---

## 📘 Proje Hakkında

**FdF (Fil de Fer)**, 42 müfredatındaki grafik tabanlı bir C projesidir.  
Amaç, bir yükseklik haritasını 3B uzayda temsil edip **izometrik projeksiyon** ile 2B ekranda tel kafes şeklinde görüntülemektir.  
Sonuç olarak, bir “tel kafes” (wireframe) modeli oluşturulur.

### 🎯 Öğrenilen Kazanımlar
- 3B → 2B **matematiksel projeksiyon** teknikleri  
- **MiniLibX** kullanarak pencere, olay ve görüntü yönetimi  
- **Bresenham algoritması** ile verimli çizgi çizimi  
- **Matris dönüşümleri** ve **vektör matematiği**

---

## 🧠 Temel Kavramlar

| Konu | Açıklama |
|------|-----------|
| 🧮 **İzometrik Projeksiyon** | 3B koordinatları 2B düzleme sabit açılarla yansıtır. |
| 🔄 **Matris Dönüşümü** | Döndürme, ölçekleme ve konum değiştirme işlemlerini yönetir. |
| ✏️ **Bresenham Algoritması** | İki nokta arasında pikselleri hesaplayarak kesintisiz çizgi oluşturur. |
| 💡 **MiniLibX** | 42’nin grafik projeleri için geliştirdiği küçük ama güçlü bir C kütüphanesidir. |

---

## ⚙️ Kurulum ve Kullanım

### 📦 Gereksinimler
- macOS veya Linux  
- `gcc` veya `clang` derleyicisi  
- MiniLibX kütüphanesi (42 projelerinde varsayılan olarak gelir)

### 🧰 Derleme

```bash
git clone https://github.com/Celtenn/fdf.git
cd fdf
make
▶️ Çalıştırma
bash
Kodu kopyala
./fdf maps/42.fdf
Program, maps/ klasöründeki .fdf uzantılı haritaları okuyarak 3B görselleştirme yapar.

🎮 Klavye Kontrolleri
Tuş	İşlev
↑ ↓ ← →	Görünümü hareket ettir
+ / -	Yakınlaştır / Uzaklaştır
Q / E	Z ekseni etrafında döndür
R	Görünümü sıfırla
ESC	Programdan çık

Kullanıcı etkileşimi MiniLibX event hook sistemi ile yönetilir.

🧩 Proje Dizini
bash
Kodu kopyala
fdf/
├── includes/
│   └── fdf.h              # Tüm yapı tanımları, prototipler
├── srcs/
│   ├── main.c             # Programın giriş noktası
│   ├── parse_map.c        # Harita okuma ve yükseklik verisi ayrıştırma
│   ├── draw.c             # Bresenham algoritmasıyla çizim işlemleri
│   ├── projection.c       # 3B -> 2B izometrik dönüşüm
│   ├── hooks.c            # Klavye olaylarının yönetimi
│   └── utils.c            # Yardımcı fonksiyonlar
├── maps/
│   ├── 42.fdf             # Örnek yükseklik haritası
│   ├── mars.fdf
│   └── pyramid.fdf
├── Makefile               # Derleme yönetimi
└── README.md
🧮 Matematiksel Arka Plan
🔹 İzometrik Projeksiyon Formülü
𝑥
′
=
(
𝑥
−
𝑦
)
×
cos
⁡
(
30
°
)
x 
′
 =(x−y)×cos(30°)
𝑦
′
=
(
𝑥
+
𝑦
)
×
sin
⁡
(
30
°
)
−
𝑧
y 
′
 =(x+y)×sin(30°)−z
Bu formül, 3B uzaydaki noktaları 2B düzleme aktarırken derinlik ve yükseklik hissi sağlar.

🔹 Bresenham Çizgi Algoritması
Bresenham algoritması, iki nokta arasındaki en yakın pikselleri seçerek kesintisiz çizgi çizer.
Bu yöntem, float kullanmadan yalnızca integer aritmetik işlemlerle çalıştığı için oldukça hızlıdır.

Örnek pseudo-kod:

c
Kodu kopyala
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
🖼️ Görsel Örnek
<p align="center"> <img src="https://github.com/Celtenn/fdf/assets/example_output.png" width="550" alt="FdF Çıktı Örneği"> </p>
🧰 Makefile Komutları
Komut	Açıklama
make	Programı derler
make clean	Ara dosyaları (.o) siler
make fclean	Tüm derlenmiş dosyaları siler
make re	Baştan derleme yapar

Makefile, otomatik bağımlılık yönetimi ve hata toleransı ile optimize edilmiştir.

🧑‍💻 Yazar
Enes Kahraman
📍 42 Kocaeli
🔗 GitHub: Celtenn

🏁 Bonus Özellikler
✅ Klavye ile dinamik döndürme

✅ Yüksekliğe göre renk geçişleri

✅ Dosya ve bellek hatası kontrolü

✅ Otomatik merkezleme ve ölçek ayarlama

✅ Hata mesajı ve argüman denetimi

✅ Esnek yapılandırma ve yeniden çizim desteği

🧾 Lisans
Bu proje, 42 Kocaeli kapsamında eğitim amaçlı olarak geliştirilmiştir.
Tüm hakları Enes Kahraman’a aittir.
Kullanım yalnızca öğrenim ve paylaşım amaçlıdır.

<p align="center">⭐ Bu proje faydalı olduysa bir yıldız bırakmayı unutma!</p> ```
