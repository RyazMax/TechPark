from django.shortcuts import render

# Create your views here.


# Отображение новейших запросов
def index(request):
    return render(request, 'index.html', {
        'questions': [[1,'GO'],[2,'STOP']],
        'header':'sometext'
    })


# Отображение самых популярных вопросов
def hot(request):
    return render(request, 'index.html', {
        'questions': [],
        'header':'sometext'
    })

# Сттраница авторизации
def signin(request):
    return render(request, 'login.html', {
        'header':'sometext'
    })

# Cтраница с одним вопросом
def question(request):
    return render(request, 'question.html')

# Страница с новым вопросом
def ask(request):
    return render(request, 'ask.html')

# Страница авторизации
def signin(request):
    return render(request, 'login.html')

# Страница регистрации
def signup(request):
    return render(request, 'signup.html')

# Cтраница профиля
def profile(request):
    return render(request, 'profile.html')