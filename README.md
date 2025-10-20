<h1 align="center">🧩 FdF — 3B Tel Kafes Görselleştirici</h1>

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
```

### ▶️ Başlatma

```bash
./fdf maps/42.fdf
```

---

## ⌨️ Klavye Kontrolleri

| Tuş | İşlev |
|:----|:------|
| ⬆️ / ⬇️ / ⬅️ / ➡️ | Görünümü hareket ettir |
| ➕ / ➖ | Yakınlaştır / Uzaklaştır |
| 🌀 Q / E | Z ekseni etrafında döndür |
| ♻️ R | Görünümü sıfırla |
| 🚪 ESC | Programdan çık |

---

## 🗂️ Proje Dizini

```
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
```

---

## 🧮 Matematiksel Arka Plan

### 🎲 İzometrik Projeksiyon

\[
x' = (x - y) \times \cos(30°)
\]  
\[
y' = (x + y) \times \sin(30°) - z
\]

---

### 📈 Bresenham Algoritması

```c
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
```

---

## 🧰 Makefile Komutları

| Komut | Açıklama |
|--------|-----------|
| `make` | Programı derler |
| `make clean` | Ara dosyaları temizler |
| `make fclean` | Tüm derleme çıktısını siler |
| `make re` | Baştan derleme yapar |

---

## 🧑‍💻 Yazar

**Enes Kahraman**  
📍 42 Kocaeli  
🔗 [GitHub: Celtenn](https://github.com/Celtenn)

---

## 🏁 Ek Özellikler

✅ Klavye ile dinamik döndürme  
✅ Yüksekliğe göre renk geçişleri  
✅ Dosya hatası kontrolü  
✅ Otomatik merkezleme ve ölçekleme  
✅ Hafif & modüler kod yapısı  

---

## 🧾 Lisans

Bu proje, **42 Kocaeli** kapsamında eğitim amaçlı olarak geliştirilmiştir.  
Tüm hakları **Enes Kahraman**’a aittir.  
Paylaşım ve öğrenim amacıyla kullanılabilir.

---

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=00C2FF&height=100&section=footer&text=⭐%20Bir%20yıldız%20bırak%20ve%20destekle!%20⭐&fontSize=20&fontColor=ffffff" />
</p>
