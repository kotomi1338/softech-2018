---
layout: page
title: プロキシの設定
permalink: /proxy/
---

## はじめに

苫小牧高専情報工学科実習室のネットワークから、外部のネットワーク（インターネット）に出るには、プロキシの設定をしなければなりません。

学生用クライアントマシンのプロキシ設定は、授業等ですでに済ませてあるはずですが、ここでは、実習用サーバ jocalc のプロキシ設定もしていきましょう。

## 初期化

まずは、これまでの設定等が残っている可能性もあるので、以下のコマンドを実行してシェルの設定ファイルを削除してください。

```
$ rm ~/.tcshrc
```

## .tcshrcファイルのコピー

次に、.tcshrcファイルを作成します。これは、情報工学科の先生がすでに書いたファイルがあるので、それを利用させてもらいます。

```
$ cp /etc/Cshrc ~/.tcshrc
```

## .tcshrcファイルの編集

今コピーしてきた.tcshrcファイルの末尾に、以下の2行を書き加えます。なお、user_nameとpasswordは、各自のCAI室のユーザ名とパスワードに読み替えてください。

```
$ setenv http_proxy "http://user_name:password@172.23.1.8:8080"
$ setenv https_proxy $http_proxy
```

## 設定ファイルの再読込

書き換えた設定ファイルを再読込します。

```
$ source ~/.tcshrc
```

## テスト

```
$ wget http://mktakuya.net
$ gcc -o hello hello.c
$ gem install gimei
```


gcc動作確認用の適当なC言語プログラム（コピペ用）


```
#include <stdio.h>

int main(void) 
{
        printf("Hello World\n");

        return 0;
}
```

