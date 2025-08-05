from flask import Flask, render_template, send_file

#Start Flask
app = Flask(__name__, static_folder='./static', )


@app.route('/')
def home():
    return render_template('page.html')

@app.route('/download')
def download():
    return send_file('static/Client.zip', as_attachment=True)

if __name__ == '__main__':
    app.run(host='0.0.0.0',port=80)