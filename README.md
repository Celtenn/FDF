# 🧩 FdF — 3B Tel Kafes Görselleştirici

<p align="center">
  <img src="https://img.shields.io/badge/Dil-C-blue.svg" />
  <img src="https://img.shields.io/badge/Okul-42-green.svg" />
  <img src="https://img.shields.io/badge/Proje-FdF-lightgrey.svg" />
  <img src="https://img.shields.io/badge/Durum-Tamamlandı-success.svg" />
</p>

<p align="center">
  <img src="https://github.com/<kullaniciadi>/fdf/assets/preview.gif" width="600" alt="FdF Önizleme">
</p>

---

## 📘 Proje Özeti

**FdF (Fil de Fer)**, 42 müfredatındaki grafik tabanlı bir C projesidir.  
Amaç, bir yükseklik haritasını 3B uzayda temsil edip **izometrik projeksiyon** kullanarak 2B ekranda tel kafes şeklinde görüntülemektir.

Bu proje sayesinde:
- 3B → 2B matematiksel dönüşümleri
- MiniLibX grafik kütüphanesinin kullanımını
- Klavye olaylarını (event handling)
- Vektör matematiği ve dönüşüm matrislerini  
öğrenmek hedeflenir.

---

## 🧠 Temel Kavramlar

| Konu | Açıklama |
|-------|-----------|
| **İzometrik Projeksiyon** | 3B noktaları 2B düzleme eşit açılarla yansıtır. |
| **Matris Dönüşümleri** | Döndürme, ölçekleme ve yer değiştirme işlemleri için kullanılır. |
| **Bresenham Algoritması** | İki nokta arasında boşluksuz çizgi çizimi sağlar. |
| **MiniLibX** | Basit grafik işlemleri için kullanılan 42’ye özel kütüphane. |

---

## ⚙️ Kurulum ve Kullanım

### Gereksinimler
- macOS veya Linux
- `gcc` derleyicisi
- MiniLibX kütüphanesi (42 ile birlikte gelir)

### Derleme

```bash
git clone https://github.com/<kullaniciadi>/fdf.git
cd fdf
make


Minilibx Kütüphanesi 2D Oyun Yapımı

MinilibX, C programlama dili için bir grafik kütüphanesidir. MinilibX, X Window System (X11) üzerinde çalışır ve X11 veri yapılarını kullanarak grafik işlemleri yapar.

Prototipler
mlx_init()
mlx_new_window()
mlx_clear_window()
mlx_loop()
mlx_xpm_file_to_image()
mlx_hook()
mlx_destroy_image()
mlx_put_image_to_window()
mlx_string_put()
Keycode Tablosu

Keycode

"mlx_init()" fonksiyonu
MinilibX kütüphanesini başlatmak için kullanılan bir fonksiyondur ve grafik işlemleri yapmak isteyen bir programcı tarafından çağrılmalıdır.

MinilibX, C programcılarının kolay ve hızlı bir şekilde grafiksel uygulamalar yazmasına olanak tanır ve X Window System ile etkileşim kurmasına izin verir.

Bu kütüphane, küçük ve basit grafiksel uygulamalar için uygun bir seçimdir.

"mlx_new_window()" fonksiyonu
MinilibX grafik kütüphanesinde bir pencere oluşturmak için kullanılan bir fonksiyondur. Bu fonksiyon, belirli bir boyutta, belirli bir başlıkla ve belirli bir ekran pozisyonunda bir pencere oluşturmanıza olanak tanır. Pencerenin özellikleri, fonksiyona verilen parametrelere göre belirlenir.

MinilibX, X Window System üzerinde çalıştığından, oluşturulan pencere, X11 veri yapılarını kullanarak X Window System tarafından yönetilir.

Pencere, grafiksel içeriğin görüntülenmesi ve kullanıcı tarafından yapılan etkileşimlerin işlenmesi için kullanılır.

"mlx_clear_window()" fonksiyonu
MinilibX grafik kütüphanesinde bir pencerenin içeriğini temizlemek için kullanılan bir fonksiyondur.

Bu fonksiyon, belirli bir renk ile belirtilen pencerenin tamamını temizler ve pencerenin arka planını belirtilen renge boyar.

Bu fonksiyon, MinilibX tarafından yönetilen pencere üzerinde grafiksel içeriklerin yenilenmesi gerektiğinde kullanılabilir.

Örneğin, kullanıcı tarafından yapılan bir işlemin sonucu olarak pencerenin içeriği değiştiğinde veya pencerenin içeriğini sıfırlamak istediğinizde bu fonksiyonu çağırabilirsiniz.

"mlx_loop()" fonksiyonu
MinilibX grafik kütüphanesinde pencere oluşturulmuş bir uygulamanın çalışmasını sürdürmesi için kullanılan bir fonksiyondur. Bu fonksiyon, pencereyi görüntüleyebilmek ve kullanıcı tarafından yapılan etkileşimleri işleyebilmek için bir döngü oluşturur.

Bu fonksiyon, pencere oluşturulduktan sonra uygulamanın çalışmasını sürdürmesi gerektiğinde kullanılır. Örneğin, pencere açıldıktan sonra kullanıcı tarafından yapılan etkileşimleri (örneğin, fare tıklama, klavye girişi) işlemek veya pencere içeriğini güncellemek için bu fonksiyon çağrılabilir.

"mlx_loop" fonksiyonu, uygulamanın sonlandığına kadar çalışmaya devam eder ve pencerenin görüntülenmesini ve etkileşimlerin işlenmesini sağlar. Uygulamanın sonlandığı zaman, bu fonksiyon otomatik olarak durdurulur.

"mlx_xpm_file_to_image()" fonksiyonu
MinilibX grafik kütüphanesinde XPM (X Pixmap) dosyalarından bir resim oluşturmak için kullanılan bir fonksiyondur. XPM dosyaları, resimlerin bitmap (ikilik) verilerini saklayan dosyalardır ve MinilibX tarafından desteklenir.

Bu fonksiyon, belirtilen XPM dosyasından resim verilerini okur ve belirtilen pencerede bu resmi görüntülemek için bir görüntü nesnesi oluşturur. Bu görüntü nesnesi, daha sonra MinilibX tarafından yönetilen pencere üzerinde kullanılabilir ve bu görüntü nesnesinin özellikleri (örneğin, boyutları, renkleri) değiştirilebilir.

Bu fonksiyon, XPM dosyalarından görüntüler oluşturmak isteyen uygulamalar için kullanışlı bir araçtır. Örneğin, oyunlar veya grafiksel kullanıcı arayüzleri için görsel içerik oluşturmak isteyen uygulamalar bu fonksiyonu kullanabilir.

"mlx_hook()" fonksiyonu
MinilibX grafik kütüphanesinde belirtilen bir etkileşim için bir kullanıcı tarafından tanımlanmış bir callback fonksiyonu tanımlamak için kullanılan bir fonksiyondur.

Bu fonksiyon, kullanıcı tarafından tanımlanmış bir callback fonksiyonu belirtilen bir etkileşim için (örneğin, fare tıklama, klavye girişi) MinilibX'e kaydeder. Callback fonksiyonu, belirtilen etkileşim gerçekleştiğinde çağrılır ve uygulamanın gerektiği gibi yanıt vermesini sağlar.

Örneğin, uygulama içinde bir pencere oluşturuldu ve kullanıcı tarafından bu pencere üzerinde bir fare tıklama gerçekleştirildiğinde uygulamanın belirli bir işlem yapması isteniyorsa, "mlx_hook" fonksiyonu kullanılarak bu işlem için bir callback fonksiyonu tanımlanabilir.

"mlx_hook()" fonksiyonu, MinilibX tarafından desteklenen tüm etkileşimler için kullanılabilir ve uygulamaların pencere oluşturulduktan sonra yapılan etkileşimleri işlemesini ve yanıt vermesini sağlar.

"mlx_destroy_image()" fonksiyonu
MinilibX grafik kütüphanesinde belirtilen bir görüntü nesnesini yok etmek için kullanılan bir fonksiyondur.

Bu fonksiyon, belirtilen görüntü nesnesi hakkındaki tüm bellek ve diğer kaynakları serbest bırakır ve bu görüntü nesnesi artık kullanılamaz hale gelir. Görüntü nesnesi, MinilibX tarafından oluşturulduysa ve "mlx_new_image" fonksiyonu kullanılarak oluşturulduysa, bu fonksiyon kullanılarak görüntü nesnesi yok edilmelidir.

Görüntü nesnesi yok edildikten sonra, bellekteki boşluk serbest hale gelir ve bu kaynaklar başka uygulamalar tarafından kullanılabilir. Ayrıca, görüntü nesnesi yok edildiğinde, görüntü nesnesi üzerinde yapılan tüm değişiklikler de geçersiz hale gelir.

"mlx_put_image_to_window()" fonksiyonu
MinilibX grafik kütüphanesinde belirtilen bir görüntü nesnesini belirtilen bir pencereye yerleştirmek için kullanılan bir fonksiyondur.

Bu fonksiyon, belirtilen görüntü nesnesini belirtilen pencereye yerleştirir ve görüntü nesnesi pencere üzerinde görüntülenir. Görüntü nesnesi, MinilibX tarafından oluşturulduysa ve "mlx_new_image" fonksiyonu kullanılarak oluşturulduysa, bu fonksiyon kullanılarak görüntü nesnesi pencereye yerleştirilmelidir.

"mlx_put_image_to_window()" fonksiyonu, görüntü nesnesini belirtilen pencereye yerleştirirken belirtilen görüntü nesnesinin boyutlarını ve pozisyonunu kullanır. Bu fonksiyon, görüntü nesnesinin pencereye yerleştirilmesi sonrasında görüntü nesnesi üzerinde yapılan değişikliklerin de pencerede görüntülenmesini sağlar.

Bu fonksiyon, görsel içeriği pencere üzerinde görüntülemek isteyen uygulamalar tarafından kullanılabilir ve görsel içeriğin pencere üzerinde görüntülenmesi ve görsel içerik üzerinde yapılan değişikliklerin görüntülenmesini sağlar.

"mlx_string_put()" fonksiyonu
MinilibX grafik kütüphanesinde belirtilen bir pencereye belirtilen bir metin dizesini yerleştirmek için kullanılan bir fonksiyondur.

Bu fonksiyon, belirtilen pencereye belirtilen metin dizesini belirtilen renk ve yazı tipi ile yerleştirir. Metin dizesi, belirtilen x ve y koordinatları üzerinde pencereye yerleştirilir.

"mlx_string_put()" fonksiyonu, pencere üzerinde metin görüntülemek isteyen uygulamalar tarafından kullanılabilir ve metin görüntülenmesi ve metin üzerinde yapılan değişikliklerin görüntülenmesini sağlar. Bu fonksiyon, metin görüntülenmesi sonrasında metin üzerinde yapılan değişikliklerin de görüntülenmesini sağlar.
