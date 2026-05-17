# VL53L5CX for Raspberry Pi Pico 2 W

Raspberry Pi Pico 2 W で STMicroelectronics VL53L5CX Time-of-Flight 8x8 マルチゾーン距離センサを動かすための Pico SDK / CMake プロジェクトです。

現在のサンプルは I2C0 経由で VL53L5CX を初期化し、4x4 解像度で測距した結果を UART に出力します。有効なターゲットが検出されたゾーンは `[*]`、それ以外は `[ ]` として 4x4 グリッド表示します。

## 構成

```text
.
├── CMakeLists.txt
├── main.c
├── pico_sdk_import.cmake
└── lib/vl53l5cx/
    ├── vl53l5cx_api.c
    ├── vl53l5cx_api.h
    ├── platform.c
    ├── platform.h
    └── LICENSE.txt
```

## ハードウェア接続

デフォルト設定は次の通りです。

| Pico 2 W | VL53L5CX |
| --- | --- |
| GP4 | SDA |
| GP5 | SCL |
| 3V3 | VIN / VCC |
| GND | GND |

I2C は `i2c0`、400 kHz で初期化されます。UART 出力は UART0、TX=GP0、RX=GP1、115200 baud です。

## 必要なもの

- Raspberry Pi Pico SDK
- CMake
- Arm GNU Toolchain
- picotool または UF2 書き込み環境
- Raspberry Pi Pico 2 W
- VL53L5CX 搭載モジュール

Pico VS Code Extension を使う場合は、`CMakeLists.txt` の設定により Pico SDK 2.2.0 系の環境を参照します。

## ビルド

```sh
mkdir -p build
cd build
cmake ..
cmake --build .
```

ビルドが成功すると、`build/VL53L5CX.uf2` などの出力が生成されます。

## 書き込み

Pico 2 W を BOOTSEL モードで接続し、生成された UF2 ファイルを書き込みます。

```sh
cp build/VL53L5CX.uf2 /Volumes/RPI-RP2/
```

環境によってマウント先は異なります。

## 実行結果

シリアルモニタを 115200 baud で開くと、初期化ステータスと測距結果が表示されます。

```text
UART stdout initialized on UART0 TX GP0 / RX GP1 at 115200 baud.
init status = 0
Print data no :   1
[*][ ][ ][ ]
[ ][ ][ ][ ]
[ ][ ][ ][ ]
[ ][ ][ ][ ]
```

`main.c` ではターゲットステータスが `5` または `6`、距離が 100 mm から 2500 mm の範囲にあるゾーンを検出ありとして表示しています。

## 設定変更

- I2C ピン: `main.c` の `I2C_SDA` / `I2C_SCL`
- I2C ポート: `main.c` の `I2C_PORT`
- 解像度: `vl53l5cx_set_resolution()` の引数
- UART 設定: `CMakeLists.txt` の `target_compile_definitions()` と `pico_enable_stdio_*()`

## ライセンス

このリポジトリのライセンスは [LICENSE.md](LICENSE.md) を参照してください。

同梱している STMicroelectronics VL53L5CX ドライバは、`lib/vl53l5cx/LICENSE.txt` に記載された条件に従います。
