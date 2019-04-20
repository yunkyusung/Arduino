#### 8x32 LED 도토 매트릭스 시계 만들기(온도,습도 표시)
- [ ] ##### **준비물**

| [아두이노(Arduino Uno)](http://mechasolution.com/shop/goods/goods_view.php?goodsno=71796&category=)  -1- | [RTC모듈(DS3231, I2C)](http://mechasolution.com/shop/goods/goods_view.php?goodsno=566721&category=132001)  -1- |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| ![](image/Arduino_Uno.jpg)                                   | ![](image/RTC.jpg)                                           |
| [온습도센서(AM2302 DHT22)](http://mechasolution.com/shop/goods/goods_view.php?goodsno=330422&category=)  -1- | [8x32 LED 도트 매트릭스(MAX7219)](http://www.devicemart.co.kr/goods/view?no=1330850)  -1- |
| ![](image/DHT22.jpg)                                         | ![](image/8x8DotMatrix.jpg)                                  |

 cf) 온습도 센서는 저렴한 [DHT11](http://mechasolution.com/shop/goods/goods_view.php?goodsno=540035&category=) 모듈을 사용해도 됨



- [ ] ##### **회로 연결**

| 아두이노 | RTC 모듈 | 온습도센서 | 도트 매트릭스 | 푸쉬버튼 |
| :------: | :------: | :--------: | :-----------: | :------: |
| D5     <br/> D6      <br/>D7     <br/>D8     <br/>D9     <br/>D10   <br/> D11    <br/> D12   <br/>A4     <br/>A5 | --------<br/>--------<br/>--------<br/>--------<br/>--------<br/>--------<br/>--------<br/>--------<br/>SDA<br/>SCL | --------<br/>--------<br/>--------<br/>--------<br/>DAT   <br/>--------<br/>--------<br/>--------<br/>--------<br/>-------- | --------<br/>--------<br/>--------<br/>--------<br/>--------<br/>CS  <br/>CLK<br/>DIN<br/>--------<br/>-------- | Mode<br/>Down<br/> Up      <br/>--------<br/>--------<br/>--------<br/>--------<br/>--------<br/>--------<br/>-------- |

![](image/wiring.jpg)

![](image/wiring2.jpg)



- [ ] ##### **동작 영상**

![](image/clock.gif)

cf) 시간을 맞추는 영상은 촬영하지 못하였음