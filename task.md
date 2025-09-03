# マイコン間のシリアル通信の補助クラスの作成

## やること

- マイコン間の高速なシリアル通信プロトコルを作成し、それに適したエンコーダーとデコーダーを作ること


## 内容

プロトコルは以下の通り
ただし、すでに送ることが確定している4byte変数の数をnとする
```cpp
最初のbyte = 0x0f

5n + 1 datatype[7:6] + dataname[5:0]
5n + 2 (uint8_t)data[0]
5n + 3 (uint8_t)data[1]
5n + 4 (uint8_t)data[2]
5n + 5 (uint8_t)data[3]

最後のbyte = 0xf0;
```

そのため、datatypeとdatanameはadressとしてenum classで定義する


```cpp
enum class uint8_t{

    //uint32_t 0b00
    PRESS = 0x01,

    //int32_t 0b01
    SampleData = 0x81,

    //float 0b10
    ACCEL_X = 0xC1,
    ACCEL_Y = 0xC2,
    ACCEL_Z = 0xC3,

}
```
###　送信側

このような操作で、簡単に扱えるようにすること
ここで、引数に1がつくものは、uint32_t、2がつくものはint32_t、3がつくものはfloatのように
adressで定義されている変数型すべてに対応できるようにオーバーロードを実装すること

Begin(),End()実行時にスタートやエンドビットを定義すること
また、getDataを実行するまでは、ptrなどのエンコードされたデータは隠蔽し、次のBegin()実行時に破棄して初期化すること
```cpp
encoder.Begin();
encoder.AddData(type1, value1);
encoder.AddData(type2, value2);
encoder.AddData(type3, value3);
encoder.End();

encoder.getData(uint8_t** ptr, uint8_t* size)
// UARTなどでの送信
```

### 受信側（割り込み受信等を想定）

setData()実行時にデコード処理を行うこと
GetData()では、typeの上位2ビットを見てvalue1に入る変数型が適切になること（ここで、ユーザーサイドは適切な変数型の引数を渡しているものとする）

```cpp
raw_data[256]//ここに受信したデータ分が入っているとする

decoder.SetData(raw_data);

decoder.getData(type1, value1);
printf(type1 + " :" + value);
```

### その他

新たに作成するファイルは、ここに作ること
そのクラス内で使う構造体の定義をのぞいて、1ファイル1クラスの定義として、実装が長くなることが予想されるため、ヘッダーとソースは分けること（lnlineをしない）
C:\Users\aoi25\Documents\PlatformIO\Projects\ESP32_P2P_Utility\src

このコードを必要に応じて参考にしてよいが、すべての要求を満たすものではない
C:\Users\aoi25\Documents\PlatformIO\Projects\ESP32_P2P_Utility\utility

関数は単語の先頭を大文字
変数やインスタンスは小文字とアンダーバーで命名してください