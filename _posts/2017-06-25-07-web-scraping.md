---
layout: post
title:  "07 Webスクレイピング入門"
date:   2017-06-25 12:00:00 +0900

---

## 自分用メモ

- nokogiriのインストール先に（時間かかるので）
- 雑談ネタ
  * W社
- できればChromeの入ってる小さい方の実習室でやりたい。。。

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

例えば、学科内サーバの僕の個人ページ [jocalc1.jo.tomakomai-ct.ac.jp/~mt17814](http://jocalc1.jo.tomakomai-ct.ac.jp/~mt17814/) は、以下のようなHTMLで記述されています。

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

今回はHTMLを書きたいわけではないので、軽い紹介のみにとどめます。Webページは、単なるテキストだけでなく、HTML（Hyper Text Markup Language）を使って記述していきます。基本的なHTMLは以下のとおりです。

{% highlight html %}
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>ページのタイトル</title>
  </head>

  <body>
    ここにページの内容を記述。
  </body>
</html>

{% endhighlight %}

HTMLは、タグというものを使って書いていきます。'<' と '>'で囲われたものをタグと呼びます。タグは基本的に開始タグと終了タグに分かれています。開始タグは '<タグ名>' と、終了タグは '</タグ名>' というように書きます。タグを含めた、タグで囲まれたまとまりを要素といいます。head要素には文字コードやタイトルなどの情報が書かれています。実際のページの中身は、body要素の中に記述していきます。

bodyタグ内でよく使われるタグとしては、以下のようなものがあります。

{% highlight html %}
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>タイトル</title>
  </head>

  <body>
    <!-- これはコメントです。 -->
    <h1>見出しレベル1</h1>
    <h2>見出しレベル2</h2>
    <p>これは段落です。</p>
    <p>段落はpタグで区切ります。</p>

    <ul>
      <li>リストです。</li>
      <li>ulタグでリストを開始して、liタグでひとつひとつの要素を書きます。</li>
    </ul>

    <a href="http://www.tomakomai-ct.ac.jp">これはリンクです。</a>

    <!-- これは画像です。 -->
    <img src="aaa.jpg">

    <!-- 表はtable要素です -->
    <table>
      <tbody>
        <!-- trは表の1行を表します。 -->
        <tr> 
          <td>tdの中にデータを書きます。</td>
          <td>tdの中にデータを書きます。</td>
        </tr>
        <tr> 
          <td>tdの中にデータを書きます。</td>
          <td>tdの中にデータを書きます。</td>
        </tr>
      </tbody>
    </table>
  </body>
</html>
{% endhighlight %}


## Nokogiriについて

RubyでHTMLをうまく扱うためのGemとして、Nokogiriというものがあります。早速、インストールしてみましょう。Tera Termを起動してjocalc1にログインし、以下のコマンドを実行してください。

```
$ gem install nokogiri
```

Nokogiriは、HTMLで記述されたWebページをRubyのオブジェクトとして扱うことができます。


## Nokogiriを使ってスクレイピングしてみる

では早速Nokogiriを使っていきましょう。irbを起動してください。

まず、nokogiriと、RubyからWebページを開くためのライブラリ open-uri を require する必要があります。

{% highlight ruby %}
require 'open-uri'
require 'nokogiri'
{% endhighlight %}

今回は、とりあえず授業変更情報のページをスクレイピングしてみましょう。以下のようにurl変数に値を代入してください。

{% highlight ruby %}
url = 'http://jyugyou.tomakomai-ct.ac.jp/jyugyou.php?class=J2'
{% endhighlight %}

URLをオープンし、それをNokogiriを利用してRubyのオブジェクトにしましょう。以下のコードで実現できます。

{% highlight ruby %}
html = Nokogiri::HTML(open(url))
{% endhighlight %}

授業変更情報はtable要素で表現されているので、まずはtable要素を抽出してみましょう。htmlオブジェクトからある要素を抽出するには、searchメソッドを使用します。

{% highlight ruby %}
html.search('table')

# searchメソッドの返り値は、配列のように扱うことができる。
html.search('table').length
{% endhighlight %}

上のコードの1行目を実行した瞬間、大量の文字列がTera Term上に表示されたと思います。授業変更情報のページにはいくつかのtable要素があるので、必要なtableのみを一旦別の変数に格納してやりましょう。

授業変更情報は10番目のtable要素なので、searchメソッドの返り値の9番目を一旦変数に格納します。（注意：Rubyの配列はC言語同様0から数えます。）

{% highlight ruby %}
table = html.search('table')[9]
{% endhighlight %}

表の1行1行は、tr要素で表現されています。授業変更情報の表を切り出したtable変数に対して、今度はtr要素をsearchし、それに対してeachを適用して授業変更の内容を表示するコードを書いてみましょう。

{% highlight ruby %}
table.search('tr').each do |tr|
  puts tr.text
end
{% endhighlight %}

若干表記が崩れていますが、とりあえず授業変更情報を取得し表示することができました。


## まとめ

今回は、Nokogiriの使い方と、授業変更情報ページを例としたWebスクレイピングの実践をやってみました。今回は取得した情報を表示だけして終わりですが、データをもっとキレイに整形・加工してデータベースに保存して、何らかの処理を行うといった事も可能です。例として、 [苫小牧高専授業変更情報bot（年上の同級生が作りました）](https://twitter.com/TmNCT_jugyo) や、 [授業変更情報のCalendarアプリ（僕が作りました）](http://jyugyou.mktakuya.net/) などがあります。

Webページから情報を取得して加工・整形して保存し、どうにかするといった処理は、今後もアプリケーションを開発していく上で必要になってくると思います。また、個人的な趣味の開発にも役立ちそうです。（例: AKBの総選挙のランキング自動取得、人気商品の在庫状況監視、学校の近くの安アパート情報収集などなど）

## 練習問題

### 1. 見出しを排除する

今回作成したプログラムでは、授業変更情報の表の見出しも一緒に出力されてしまっていました。見出しは表示せず、純粋な授業変更情報のみを表示するようにプログラムを作り変えてください。

ヒント： each_with_indexメソッドを使うと良さそう。 [参考リンク](https://docs.ruby-lang.org/ja/2.4.0/method/Enumerable/i/each_with_index.html)

{% highlight ruby %}
# each_with_indexメソッドの使い方

ary = ['りんご', 'バナナ', 'パイナップル', 'ペン', 'アップル']

ary.each_with_index do |item, i|
  puts "#{i}番目: #{item}"
end
{% endhighlight %}


### 2. クラス化してみる

今回作成したプログラムを、クラス化して、再利用できるようにしてみましょう。

ファイル名は 'schedule-checker.rb' クラス名は ScheduleChecker とします。仕様は、以下のとおりです。

- initializeメソッド
  * インスタンス変数への値のセット
  * 引数 class_name 各クラスの名称（情報5年→J5、2年5組→J2）
- インスタンス変数
  * @changes 授業変更情報（文字列）の配列
  * @url スクレイピングの対象とするWebページのURL（文字列）
- インスタンスメソッド
  * fetch 授業変更情報を取得し、インスタンス変数@changesにセットする。
  * display 授業変更情報を表示する。

以下は、ScheduleCheckerクラスの雛形です。

{% highlight ruby linenos %}
class ScheduleChecker
  def initialize(class_name)
  	@changes = []
	@url = "http://jyugyou.tomakomai-ct.ac.jp/jyugyou.php?class=#{class_name}"
  end

  def fetch
  	# 授業変更情報を取得し@changesに格納
  end

  def display
  	# 授業変更情報の表示
  end
end
{% endhighlight %}

また、実行用のRubyプログラムは、main.rbとします。main.rbは以下のとおりです。

{% highlight ruby linenos %}
# 自作のファイルをrequireするときは、パスの指定が必要
require './schedule-checker'

schedule_checker = ScheduleChecker.new('J2')
schedule_checker.fetch 		# 授業変更情報を取得し、インスタンス変数@changesにセット
schedule_checker.display 	# J2（2年5組）の授業変更情報が出力される
{% endhighlight %}

なお、Ruby標準のライブラリや、gemコマンドでインストールしたgem以外の、自作のファイルをrequireする場合は、 `require './schedule-checker'` のように `./` 等でパスを指定してやらなければなりません。


### 3. 全クラスの授業変更情報を取得する

今回作成したプログラムでは、2年5組の情報しか取得できませんでした。すべてのクラスの授業変更情報を取得できるようにプログラムを作り変えてください。（各クラスの名称を配列に突っ込んで、eachで回してやると良い。）


### 4. 日程と授業変更内容を分割する

今回作成したプログラムでは、授業変更の日程（日付と時間）と、変更内容がひとつになっていました。

取得した情報を日程と変更内容で分割しハッシュにまとめ、それらをインスタンス変数@changes配列に格納してください。

```
# こんな感じ
@changes
#=> 
[
  { date: '7月18日(火) 5・6時限目', content: 'プログラミングⅠ→論理回路Ⅰ' },
  { date: '7月20日(水) 1・2時限目', content: '論理回路Ⅰ→プログラミングⅠ' }
]
```

### 5. 授業変更情報をCSVファイルに書き込んでみる

今回作成したScheduleCheckerクラスに、授業変更情報をCSVファイルに書き込むインスタンスメソッド `output_to_csv` を追加しましょう。

仕様は、以下のとおりです。

- 書き込むCSVのファイル名は、 `J2.csv` のように、initializeメソッドで受け取ったclass_name変数の値を使うこと。
- CSVファイルは、以下のようなフォーマットであること。

```
日程,内容
7月18日(火) 5・6時限目,プログラミングⅠ→論理回路Ⅰ
7月20日(水) 1・2時限目,論理回路Ⅰ→プログラミングⅠ
```

なお、CSVファイルへの書き込みの方法は、Rubyのドキュメントや、Google検索で出てきた記事を参照してください。
[参考](https://docs.ruby-lang.org/ja/latest/class/CSV.html)

