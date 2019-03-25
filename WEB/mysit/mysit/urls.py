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
from django.conf import settings
from django.conf.urls.static import static

from questions import views
# from . import views

urlpatterns = [
    path('',views.index, name='questions_index'),
    path('hot/', views.hot, name='questions_hot'),
    path('tags/<str:tag_name>', views.withTag, name="questions_withtag"),
    path('login/', views.signin, name='questions_signin'),
    path('logout/', views.logout, name='questions_logout'),
    path('signup/', views.signup, name='questions_signup'),
    path('question/<int:question_id>', views.question, name='questions_question'),
    path('ask/', views.ask, name='questions_ask'),
    path('profile', views.profile, name='questions_profile'),
    path('admin/', admin.site.urls),
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
