import processing.serial.*;

Serial myPort;
int iAngle;
int iDistance;

void setup() {
  size(1300, 800);
  smooth();
  myPort = new Serial(this, "COM4", 9600);
  myPort.clear();
  myPort.bufferUntil('.');
}

void draw() {
  fill(98, 245, 31);
  noStroke();
  fill(0, 4);
  rect(0, 0, width, 0.935 * height);
  fill(98, 245, 31);
  DrawRadar();
  DrawLine();
  DrawObject();
  DrawText();
}

void serialEvent(Serial myPort) {
  try {
    String data = myPort.readStringUntil('.');
    if (data == null) return;
    data = trim(data);
    int commaIndex = data.indexOf(",");
    if (commaIndex == -1) return;
    String angle    = data.substring(0, commaIndex);
    String distance = data.substring(commaIndex + 1);
    iAngle    = StringToInt(angle);
    iDistance = StringToInt(distance);
  } catch(RuntimeException e) {}
}

void DrawRadar() {
  pushMatrix();
  translate(width / 2, 0.926 * height);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  DrawRadarArcLine(0.9375);
  DrawRadarArcLine(0.7300);
  DrawRadarArcLine(0.5210);
  DrawRadarArcLine(0.3130);
  final int halfWidth = width / 2;
  line(-halfWidth, 0, halfWidth, 0);
  for (int angle = 30; angle <= 150; angle += 30) {
    DrawRadarAngledLine(angle);
  }
  popMatrix();
}

void DrawRadarArcLine(final float coefficient) {
  arc(0, 0, coefficient * width, coefficient * width, PI, TWO_PI);
}

void DrawRadarAngledLine(final int angle) {
  line(0, 0, (-width / 2) * cos(radians(angle)), (-width / 2) * sin(radians(angle)));
}

void DrawObject() {
  pushMatrix();
  translate(width / 2, 0.926 * height);
  strokeWeight(9);
  stroke(255, 10, 10);
  int pixsDistance = int(iDistance * 0.020835 * height);
  if (iDistance < 20 && iDistance != 0) {
    float c = cos(radians(iAngle));
    float s = sin(radians(iAngle));
    int x1 = +int(pixsDistance * c);
    int y1 = -int(pixsDistance * s);
    int x2 = +int(0.495 * width * c);
    int y2 = -int(0.495 * width * s);
    line(x1, y1, x2, y2);
  }
  popMatrix();
}

void DrawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(width / 2, 0.926 * height);
  float angle = radians(iAngle);
  int x = int(+0.88 * height * cos(angle));
  int y = int(-0.88 * height * sin(angle));
  line(0, 0, x, y);
  popMatrix();
}

void DrawText() {
  pushMatrix();
  fill(0, 0, 0);
  noStroke();
  rect(0, 0.9352 * height, width, height);
  fill(98, 245, 31);
  textSize(20);
  text("5cm",  0.6146 * width, 0.9167 * height);
  text("10cm", 0.7190 * width, 0.9167 * height);
  text("15cm", 0.8230 * width, 0.9167 * height);
  text("20cm", 0.9271 * width, 0.9167 * height);
  textSize(35);
  text("Object: " + (iDistance > 20 || iDistance == 0 ? "Out of Range" : "In Range"), 0.05 * width, 0.9723 * height);
  text("Angle: " + iAngle + " deg", 0.52 * width, 0.9723 * height);
  text("Distance: " + (iDistance == 0 ? "---" : iDistance + " cm"), 0.74 * width, 0.9723 * height);
  textSize(20);
  fill(98, 245, 60);
  translate(0.5006 * width + width / 2 * cos(radians(30)), 0.9093 * height - width / 2 * sin(radians(30)));
  rotate(-radians(-60));
  text("30", 0, 0);
  resetMatrix();
  translate(0.497 * width + width / 2 * cos(radians(60)), 0.9112 * height - width / 2 * sin(radians(60)));
  rotate(-radians(-30));
  text("60", 0, 0);
  resetMatrix();
  translate(0.493 * width + width / 2 * cos(radians(90)), 0.9167 * height - width / 2 * sin(radians(90)));
  text("90", 0, 0);
  resetMatrix();
  translate(0.487 * width + width / 2 * cos(radians(120)), 0.9287 * height - width / 2 * sin(radians(120)));
  rotate(radians(-30));
  text("120", 0, 0);
  resetMatrix();
  translate(0.4896 * width + width / 2 * cos(radians(150)), 0.9426 * height - width / 2 * sin(radians(150)));
  rotate(radians(-60));
  text("150", 0, 0);
  popMatrix();
}

int StringToInt(String s) {
  int value = 0;
  s = trim(s);
  for (int i = 0; i < s.length(); ++i) {
    if (s.charAt(i) >= '0' && s.charAt(i) <= '9') {
      value *= 10;
      value += (s.charAt(i) - '0');
    }
  }
  return value;
}
