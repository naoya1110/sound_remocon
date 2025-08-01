# sound_remocon

このリポジトリは、サウンドリモコンの開発データ（KiCadファイル等）をまとめたものです。

## ディレクトリ構成

- **v2/**  
  バージョン2
  - **kicad/**  
    v2用のKiCadプロジェクトファイル
    - `sound_remocon_v2/`：v2用KiCadプロジェクト・Gerberファイル
    - `plot_v2_20250704/`：v2 PCB製造用Gerberファイル
  - **ltspice/**  
    LTspiceシミュレーションファイル
    - `mixer_circuit_simulation.asc`：ミキサー回路シミュレーション
  - **pico_codes/**  
    - `pico_codes\sound_remocon_v2\sound_remocon_v2.ino` ラズパイPico用ファームウェア・コード

- **v1/**  
  バージョン1
  - **kicad/**  
    KiCadプロジェクトファイル、ネットリスト、シンボルライブラリ、フットプリント、Gerberファイルなど。


