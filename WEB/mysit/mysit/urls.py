"""mysit URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from django.conf.urls import url

from questions import views
# from . import views

urlpatterns = [
    url(r'^$', views.index, name='questions_index'),
    url(r'^hot/', views.hot, name='questions_hot'),
    url(r'^login/', views.signin, name='questions_signin'),
    url(r'^signup/', views.signup, name='questions_signup'),
    url(r'^question/', views.question, name='questions_question'),
    url(r'^ask/', views.ask, name='questions_ask'),
    url(r'^profile', views.profile, name='questions_profile'),
    url(r'^admin/', admin.site.urls),
]
