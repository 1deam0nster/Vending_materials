from flask import Blueprint, url_for, render_template, abort
from jinja2 import TemplateNotFound


api_bp = Blueprint('api_bp', __name__, template_folder='templates', static_folder='static' )

@api_bp.route("/api")
@api_bp.route('/')
def api_index():
    # return url_for('admin.index')
    return url_for('.index')
