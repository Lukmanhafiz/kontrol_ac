# 🌡️ ESP32 Air Conditioner Controller via Node-RED Dashboard

Proyek ini memungkinkan pengendalian **AC (Air Conditioner)** menggunakan **ESP32** melalui **Node-RED Dashboard**.  
ESP32 menerima perintah ON/OFF dan pengaturan suhu dari dashboard, lalu mengirimkan sinyal **IR (infrared)** ke AC menggunakan library `IRremoteESP8266`.

---

## 🧩 Fitur Utama

- ✅ Kontrol **AC ON/OFF** dari dashboard web Node-RED  
- 🌡️ Ubah suhu (16°C – 30°C) langsung dari dashboard  
- 🔁 Komunikasi real-time menggunakan **WebSocket**  
- 📡 ESP32 mengirim status AC kembali ke Node-RED  
- 🧠 Mendukung tombol fisik untuk ON/OFF AC  
- 🔌 Dapat dijalankan secara lokal di jaringan WiFi  

---

## 🏗️ Struktur Proyek

```
📦 kontrol-ac
├── .gitignore
├── platformio.ini
├── main.cpp
└── kontrolac.json   ← Flow Node-RED Dashboard
```

---

## ⚙️ Perangkat yang Digunakan

| Komponen | Keterangan |
|-----------|-------------|
| 🧠 ESP32 DevKit V1 | Mikrokontroler utama |
| 📡 IR LED (Pin D4) | Mengirim sinyal infrared ke AC |
| 🔘 Tombol 1 (Pin D18) | Tombol manual untuk menyalakan AC |
| 🔘 Tombol 2 (Pin D19) | Tombol manual untuk mematikan AC |
| 🌐 Node-RED | Server dashboard dan komunikasi WebSocket |

---

## 🔧 Instalasi

### 1️⃣ Clone Repository

```bash
git clone https://github.com/<yourusername>/kontrol-ac.git
cd kontrol-ac
```

### 2️⃣ Buka dengan PlatformIO

Pastikan sudah menginstal [PlatformIO IDE](https://platformio.org/install/ide?install=vscode).

Kemudian buka folder proyek ini dan sesuaikan koneksi WiFi pada file `main.cpp`:

```cpp
const char* ssid = "NOC";
const char* password = "noc2023!";
```

Jika perlu, ubah alamat Node-RED:
```cpp
const char* host = "192.168.223.68"; // IP Node-RED
const int port = 1880;
const char* path = "/ws/ac";         // WebSocket endpoint
```

Lalu upload kode ke ESP32.

---

## 🌍 Setup Node-RED

1. Buka Node-RED Editor di browser (`http://<ip-node-red>:1880`)
2. Import file `kontrolac.json`
3. Deploy flow
4. Akses dashboard di `http://<ip-node-red>:1880/ui`

Dashboard akan menampilkan:
- Tombol **AC ON**
- Tombol **AC OFF**
- Pengaturan suhu
- Status AC saat ini

---

## 🧠 Penjelasan Singkat Komponen Kode

### `main.cpp`
- Menghubungkan ESP32 ke WiFi
- Menginisialisasi IR LED dan library `IRremoteESP8266`
- Menjalankan komunikasi WebSocket ke Node-RED
- Mengatur aksi ketika tombol ditekan atau pesan diterima

### `kontrolac.json`
- Flow Node-RED untuk mengontrol AC dan menampilkan dashboard
- Menggunakan node `ui_button`, `ui_numeric`, dan `websocket in/out`

### `platformio.ini`
- Mengatur dependensi dan konfigurasi PlatformIO:
  ```ini
  lib_deps = 
      IRremoteESP8266
      links2004/WebSockets@^2.7.0
  ```

---

## 🖼️ Tampilan Dashboard

**Dashboard Node-RED:**
```
+---------------------------+
| [AC ON]  [AC OFF]         |
| Suhu: [ 24°C ]            |
| Status: AC ON             |
+---------------------------+
```

---

## 📜 Lisensi

Proyek ini bersifat **open source** di bawah lisensi MIT.  
Silakan gunakan, ubah, dan kembangkan sesuai kebutuhan.

---

## 👤 Author

**Lukman Hafiz**  
📧 harusdapetemas22@gmail.com
💻 GitHub: github.com/Lukmanhafiz

