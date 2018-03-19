from django.http import HttpResponse
from django.shortcuts import render

# Главная страница со списком вопросов
def showIndex(request):
    return render(request, 'index.html', {'questions':list(range(5))})

# Страница с одним вопросом
def showQuestion(request):
    return render(request, 'question.html')

# Страница с новым вопросом
def showAsk(request):
    return render(request, 'ask.html')

# Страница авторизации
def showLogIn(request):
    return render(request, 'login.html')

# Страница регистрации
def showSignUp(request):
    return render(request, 'signup.html')

# Cтраница профиля
def showProfile(request):
    return render(request, 'profile.html')