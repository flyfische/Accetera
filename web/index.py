from flask import Flask, render_template, request
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def hello_world(name=None):
    if request.method == 'POST':
        if request.form['submit'] == 'inc':
            target = open('/media/sdcard/setTemp.txt','r+')
            cur = target.read()
            cur = float(cur) + 1.0
            target.seek(0)
            target.write(str(cur))
            target.truncate()
            target.close()
        if request.form['submit'] == 'dec':
            target = open('/media/sdcard/setTemp.txt','r+')
            cur = target.read()
            cur = float(cur) - 1.0
            target.seek(0)
            target.write(str(cur))
            target.truncate()
            target.close()
    txt = open('/media/sdcard/current.txt')
    temp = txt.read()
    set = open('/media/sdcard/setTemp.txt')
    settemp = set.read()
    return render_template('hello.html', temp=temp, settemp=settemp)
@app.route('/inc')
def increase_temp():
    return 'Increase'
@app.route('/dec')
def decrease_temp():
    return 'Decrease'

if __name__ == '__main__':
    app.debug = True
    app.run(host='0.0.0.0')
