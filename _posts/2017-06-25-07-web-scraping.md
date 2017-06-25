---
layout: post
title:  "07 Webスクレイピング入門"
date:   2017-06-25 12:00:00 +0900

---

## はじめに

実践的なプログラミングの第一歩として、Webスクレイピングをやってみましょう。Webスクレイピングとは、Webサイトから必要な情報を抽出する技術のことです。

例えば、任天堂のWebサイトから、発売予定のSwitchのゲームソフトの情報、具体的にはタイトルと発売日を取得したいとします。任天堂Webサイトの「今後発売予定のソフトウェア」は、以下のようなWebページです。

![任天堂Webサイトの今後発売予定のソフトウェアページ]({{ site.baseurl }}/images/switch-softwares.gif)

Webページには、サイトの飾り付けや画像と一緒に、様々な情報が表示されています。今回必要なのは、タイトルと発売日のみです。任天堂のWebサイトをスクレイピングするプログラムを書いて、タイトルと発売日を取得し、CSVファイルにまとめてみました。


![Switch発売予定のソフトのCSV]({{ site.baseurl }}/images/switch-softwares-csv.png)

[ソースコードはここ](https://github.com/mktakuya/switch-softwares)

このCSVファイルの情報を使って、あとはGoogleカレンダーに表示するなり、ゲームの発売日が近づいてきたらツイートしてお知らせするbotを作るなり、いろいろと遊ぶことができます。

このように、Webページから必要な情報を抜き出す事を、Webスクレイピングといいます。

## HTMLについて

Webページは、HTMLという言語で記述されています。

例えば、学科内サーバの僕の個人ページ [http://jocalc1.jo.tomakomai-ct.ac.jp/~mt17814/](http://jocalc1.jo.tomakomai-ct.ac.jp/~mt17814/) は、以下のようなHTMLで記述されています。

{% highlight html %}
<!DOCTYPE html>
<html lang="ja">
  <head>
    <meta charset="UTF-8">
    <title>AP1 向平卓矢のページ</title>
  </head>

  <body>
    <h1>向平卓矢のページへようこそ！</h1>
    <p>ここには、いろいろ置いています。</p>

    <h2>プロフィール</h2>
    <ul>
      <li>電子・生産システム工学専攻 1年</li>
      <li>情報工学科23期（2017年3月卒業）</li>
      <li>ソフトウェアテクノロジー部 所属</li>
    </ul>

    <h2>好きなもの</h2>
    <ul>
      <li>インターネット</li>
      <li>ブログ</li>
      <li>Podcast</li>
      <li>休日のドライブ</li>
      <li>水曜どうでしょう</li>
      <li>旅行</li>
    </ul>

    <h2>コンテンツ</h2>
    <ul>
      <li><a href="http://tnct-softech2016.github.io/">ソフテク2016 C言語</a></li>
      <li><a href="https://mktakuya.github.io/softech-2017/">ソフテク2017 Ruby</a></li>
    </ul>
  </body>
</html>
{% endhighlight %}

## Webスクレイピングについて


## Nokogiriについて

## Nokogiriを使ってスクレイピングしてみる
