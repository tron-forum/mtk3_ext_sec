# μT-Kernel 3.0 セキュア機能拡張 構築手順書 <!-- omit in toc -->
# STM32N657-NUCLEO 向け <!-- omit in toc -->
## Version.1.00.00 <!-- omit in toc -->
## 2026.01.29 <!-- omit in toc -->

# 1. 概要
## 1.1. 目的
本書は、トロンフォーラムからソースコードが公開されているμT-Kernel 3.0 セキュア機能拡張の開発環境の構築手順を示す。
対象とするµT-Kernel 3.0およびセキュア機能拡張を以下に示す。

| 分類   | 名称      | バージョン   | URL(GitHub)                                                 |
| ---- | ------------------------------ | ------- | ------------------------------------------ |
| OS   | μT-Kernel      | 3.00.08 | https://github.com/tron-forum/mtkernel_3/releases   |
| 機能拡張 | μT-Kernel 3.0 セキュア機能拡張 | 1.00   | https://github.com/tron-forum/mtk3_ext_sec/releases |

## 1.2. ファイル構成
μT-Kernel 3.0 セキュア機能拡張のGitHubリポジトリに公開されているファイル構成を以下に示す。

mtk3_ext_sec
  + mtk3_nonsecure　　　　　　　　　　　非セキュアプログラム
  |    + ext_sec　　　　　　　　　　　　　　　セキュア機能拡張・非セキュア部
  |    + mtkernel　　　　　　　　　　　　　　 μT-Kenrel 3.0 (※)
  |　　　　　　　　　　　　　　　　　　
  + mtk3_secure　　　　　　　　　　　　　セキュアプログラム
  |    + config　　　　　　　　　　　　　　　 コンフィギュレーションファイル
  |    + include　　　　　　　　　　　　　　　定義ファイル
  |    + ext_sec　　　　　　　　　　　　　　　セキュア機能拡張・セキュア部
  |
  + documents

(※) μT-Kernel 3.0はサブモジュールとして含まれている。

## 1.3. 対象ハードウェア
対象OSおよびハードウェアを以下に示す。

| マイコンボード         | マイコン        | CPUコア          | 識別子(※)                  | メーカー            |
| --------------- | ----------- | -------------- | -------------------------- | -------------- |
| NUCLEO-N657X0-Q | STM32N657X0 | Arm Cortex-M55 | \_STM32_NUCLEO_N657_EXTSEC_ | STマイクロエレクトロニクス |

(※)識別子は開発プロジェクトの作成時に対象ボードを指定するため使用する。

## 1.4. 開発環境・ツール
使用する開発環境・ツールを以下に示す。また本書の動作を確認したバージョンを記す。

| 分類        | 名称           | バージョン  | メーカー             |
| --------- | ------------ | ------ | -------------- |
| 統合開発環境    | STM32CubeIDE | 2.0.0  | STマイクロエレクトロニクス |
| コンフィギュレータ | STM32CubeMX  | 6.16.1 | STマイクロエレクトロニクス |

# 2. プロジェクトの作成手順
開発プロジェクトの作成手順を以下に示す。

## 2.1. プロジェクトのコンフィギュレーションと生成
### 2.1.1. プロジェクトの生成手順
STM32CubeMXを使用して以下の手順で、対象ハードウェアの開発プロジェクトの設定および生成を行う。

(1) メニュー[FIle]から[New Project]を選択し、 対象マイコンボードを選ぶ。
(2) [Secure and Non Secure domain]を選択してプロジェクトを生成する。
(3) 各項目の設定は、開発するアプリケーションに応じて必要な値とする。

生成されたプロジェクトは以下の3つのサブプロジェクトから構成される。

- FSBL　　　　　　　FSBL(First Stage Boot Loader)プロジェクト
- AppliSecure　　　セキュアアプリ・プロジェクト
- AppliNonSecure　　非セキュアアプリ・プロジェクト

### 2.1.2. プロジェクトの設定例
トロンフォーラムから公開しているμT-Kernelセキュア機能拡張のサンプルプロジェクトの設定を以下に示す。

#### 2.1.2.1. クロック設定 (Clock Configuration)
| 項目   | 周波数                |
| ---- | ------------------ |
| PLL1 | 1200MHz            |
| IC1  | PLL1 /2 = 600MHz   |
| IC2  | PLL1 /3 = 400MHz   |
| IC6  | PLL1 /3 = 400MHz   |
| IC11 | : PLL1 /4 = 300MHz |

| 項目   | 周波数                |
| ---- | ------------------ |
|CPU Clock Mux| IC1を選択|
|System Clock Mux SYSB| IC2を選択|
|System Clock Mux SYSC| IC6を選択|
|System Clock Mux SYSD| IC11を選択|

#### 2.1.2.2. メモリ
FSBL(First Stage Boot loader)により、アプリケーションは外部FLASHメモリから内蔵RAMに転送され、実行される。
内蔵RAMのメモリマップを以下に示す。

| 領域               | 先頭         | サイズ    |
| ---------------- | ---------- | ------ |
| FSBL             | 0x34180400 | 512KB  |
| Secure Appli     | 0x34000000 | 1024KB |
| Non Secure Appli | 0x24100000 | 1024KB |

#### 2.1.2.3. ペリフェラル
サンプルプロジェクトでは以下のペリフェラルを有効としている。

(1) オンボードLED
| LED種別 | ポート番号 |  割り当て  |
| ----- | ----- | --------------- |
| 緑色LED | PG0   | Secure Appli    |
| 青色LED | PG8   | FSBL            |
| 赤色LED | PG10  | NonSecure Appli |

(2) デバッグ用UART
| 信号        | ポート番号 | 割り当て               |
| --------- | ----- | ------------------ |
| USART1-TX | PE5   | Secure & NonSecure |
| USART1-RX | PE6   | Secure & NonSecure |

## 2.2. プロジェクトへのμT-Kernelの組み込み
STM32CubeiDEを使用して以下の手順で、前項で生成したプロジェクトにμT-Kenrel 3.0およびセキュア機能拡張を組み込む。

### 2.2.1. セキュアアプリ・プロジェクトへの組み込み手順
(1) セキュアアプリ・プロジェクト(AppliSecure)のディレクトリに、セキュア機能拡張のmtk3_secureディレクトリをコピーする。サブプロジェクトのディレクトリ直下に置くこととする。
(2) Cコンパイラのプリプロセッサのシンボル定義に、対象ハードウェアの識別子を定義する（例：NUCLEO-N657X0-Qの場合は、識別子\_STM32_NUCLEO_N657_EXTSEC_を定義する）。
(3) Cコンパイラのインクルードパスに以下を定義する。
```
"${workspace_loc:/${ProjName}/mtk3_secure/config}"
"${workspace_loc:/${ProjName}/mtk3_secure/include}"
```
(4) アセンブラのプリプロセッサのシンボル定義に、(3)と同じ識別子を定義する。
(5) アセンブラのインクルードパスに、(4)と同じパスを指定する。
(6) mtk3_secureディレクトリのビルドを有効とし、セキュアアプリ・プロジェクトをビルドする。

### 2.2.2. 非セキュアアプリ・プロジェクトへの組み込み手順
(1) 非セキュアアプリ・プロジェクト(AppliNonSecure)に、セキュア機能拡張のmtk3_nonsecureディレクトリをコピーする。サブプロジェクトのディレクトリ直下に置くこととする。
(2) Cコンパイラのプリプロセッサのシンボル定義に、対象ハードウェアの識別子を定義する（例：NUCLEO-N657X0-Qの場合は、識別子\_STM32_NUCLEO_N657_EXTSEC_を定義する）。
(3) Cコンパイラのインクルードパスに以下を定義する。
```
"${workspace_loc:/${ProjName}/mtk3_nonsecure/mtkernel}"
"${workspace_loc:/${ProjName}/mtk3_nonsecure/mtkernel/config}"
"${workspace_loc:/${ProjName}/mtk3_nonsecure/mtkernel/include}"
"${workspace_loc:/${ProjName}/mtk3_nonsecure/mtkernel/kernel/knlinc}"
"${workspace_loc:/${ProjName}/mtk3_nonsecure/ext_sec}"
```
(4) アセンブラのプリプロセッサのシンボル定義に、(3)と同じ識別子を定義する。
(5) アセンブラのインクルードパスに、(4)と同じパスを指定する。
(6) `AppliNonSecure/Core/Src/main.c`ファイルの`/* USER CODE BEGIN 2 */`～`/* USER CODE END 2 */`の間に以下のμT-Kenrel起動関数の呼び出しを記述する。
```C
  /* USER CODE BEGIN 2 */
  void knl_start_mtkernel(void);
  knl_start_mtkernel();
  /* USER CODE END 2 */
```
(7) mtk3_nonsecureディレクトリのビルドを有効とし、非セキュアアプリ・プロジェクトをビルドする。

# 3. アプリケーション
## 3.1. アプリケーションの場所
µT-Kernel 3.0のアプリケーションは、セキュアアプリ・プロジェクト(ApliNonSecure)のディレクトリ下の任意の場所に置くことが出来る。
T-Kernel 3.0 セキュア機能拡張のGitHubリポジトリから公開しているサンプルプロジェクトでは、ApliNonSecure直下にApplicationディレクトリを設け、そこにアプリケーションのプログラムを置いている。

## 3.2. サンプル・アプリケーション
T-Kernel 3.0 セキュア機能拡張のGitHubリポジトリから公開しているサンプルプロジェクトでは、以下の動作のプログラムが含まれている。

(1) 起動するとFSBLが青色LEDを1度点滅させ点灯状態とする。
(2) 続いて、セキュアアプリで緑色LEDを1度点滅させ点灯状態とする。
(3) 非セキュアのμT-Kernel 3.0のタスクにて、赤色LEDを0.5秒間隔で点滅する。

# 変更履歴

| 版数      | 日付         | 内容   |
| ------- | ---------- | ---- |
| 1.00.00 | 2026.01.29 | 初版 |