from flask import Flask, render_template, redirect, url_for
from forms import CourseForm

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your secret key'


courses_list = [{
    'title': 'Python 101',
    'description': 'Learn Python basics',
    'price': 34,
    'available': True,
    'level': 'Beginner'
    },{
    'title': 'Python 102',
    'description': 'Learn Python basics',
    'price': 34,
    'available': True,
    'level': 'Beginner'
    }]

courses_list2 = [{
    'sugar': 1,
    }]


@app.route('/', methods=('GET', 'POST'))
def index():
    form = CourseForm()
    if form.validate_on_submit():
        courses_list.append({'title': form.title.data,
                             'description': form.description.data,
                             'price': form.price.data,
                             'available': form.available.data,
                             'level': form.level.data
                             })
        return redirect(url_for('courses'))
    return render_template('index2.html', form=form)

# @app.route('/add', methods=('GET', 'POST'))
# def index():
#     form = CourseForm()
#     if form.validate_on_submit():
#         courses_list.append({'sugar': form.sugar.data})
#         return redirect(url_for('bye'))
#     return render_template('add.html', form=form)

@app.route('/bye/')
def courses():
    return render_template('bye.html', courses_list2=courses_list2)

@app.route('/courses/')
def courses():
    return render_template('courses.html', courses_list=courses_list)


if __name__ == '__main__':
    app.debug = True
    app.run(host='127.0.0.1')