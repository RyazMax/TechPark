from django.shortcuts import render, redirect, reverse
from django.core.paginator import Paginator
from django.contrib.auth import authenticate
from django.contrib.auth.decorators import login_required
import django.contrib.auth as auth
from django.core.files.base import ContentFile
from django.core.files import File
import os

from .models import *
from .forms import AskForm, RegisterForm, LoginForm, AnswerForm, ProfileEditForm
from  mysit.settings import MEDIA_ROOT, MEDIA_URL


# Create your views here.

variableDict = {
    'bestUsers':Profile.objects.best(),
    'popularTags':Tag.objects.popular()
}



def listing(request, object_list, obj=None):
    paginator = Paginator(object_list, 4)
    if obj != None:
        for i in paginator.page_range:
            if obj in paginator.get_page(i).object_list:
                return paginator.get_page(i)
    page = request.GET.get('page', 1)
    objects = paginator.get_page(page)
    return objects

# Отображение новейших запросов
def index(request):
    variableDict['subCategory'] = 'hot'
    questions = listing(request, Question.objects.newest())
    variableDict['questions'] = questions
    variableDict['title'] = 'New questions'
    variableDict['subTitle'] = 'Hot questions'
    return render(request, 'index.html', variableDict)

def withTag(request, tag_name):
    questions = listing(request, Question.objects.withTag(tag_name))
    variableDict['questions'] = questions
    variableDict['title'] = 'Tag: '+tag_name
    variableDict['subTitle'] = ''
    return render(request, 'index.html', variableDict)

# Отображение самых популярных вопросов
def hot(request):
    variableDict['subCategory'] = ''
    questions = listing(request, Question.objects.hotest())
    variableDict['questions'] = questions
    variableDict['title'] = 'Hot questions'
    variableDict['subTitle'] = 'New questions'
    return render(request, 'index.html', variableDict)


# Cтраница с одним вопросом
def question(request, question_id):
    question_page = Question.objects.get(pk = question_id)
    form = AnswerForm(request.POST)
    if request.POST:
        if form.is_valid():
            answer = Answer.objects.create(question=question_page,
                                           text=form.cleaned_data.get('textarea'),
                                           author=request.user.profile)
            page_num = int(question_page.answer_set.count()/4)+1
        return redirect(request.path+'?page='+str(page_num)+'#'+str(answer.id))
    answers = listing(request, question_page.answer_set.all())
    variableDict.update({'question': question_page,
                        'answers': answers,
                        'form': form})
    return render(request, 'question.html', variableDict)


# Страница с новым вопросом
@login_required(login_url='/login')
def ask(request):
    form = AskForm(request.POST)
    if request.POST:
        if form.is_valid():
            tags = form.cleaned_data.get('tags')
            if tags:
                tags = tags.split()
                Tag.objects.create_from_list(tags)
            question = Question.objects.create(title=form.cleaned_data.get('title'),
                                                text=form.cleaned_data.get('text'),
                                                author=request.user.profile)
            question.add_tags(tags)
            return redirect(
                reverse('questions_question', args=[question.id])
            )
    variableDict.update({'form': form})
    return render(request, 'ask.html', variableDict)


# Страница авторизации
def signin(request):
    next_page = request.GET.get('next', '/')
    form = LoginForm(request.POST)
    if request.POST:
        form = LoginForm(request.POST)
        if form.is_valid():
            user = auth.authenticate(username=form.cleaned_data.get('login'),
            password=form.cleaned_data.get('Password'))

            if user is not None:
                auth.login(request, user)
                return redirect(next_page)
            else:
               form.add_error(None, 'Wrong login or password')
    variableDict.update({'form': form})
    return render(request, 'login.html', variableDict)

def logout(request):
    auth.logout(request)
    next_page = request.GET.get('stay', '/')
    return redirect(next_page)

# Страница регистрации
def signup(request):
    form = RegisterForm(request.POST)
    if request.POST:
        if form.is_valid():
            name = form.cleaned_data.get('login')
            email = form.cleaned_data.get('email')
            password = form.cleaned_data.get('password')
            rep_password = form.cleaned_data.get('rep_password')
            if password != rep_password:
                form.add_error(None, 'Passwords do not match')
            elif Profile.objects.is_exist(name, email):
                form.add_error(None, 'User with this login already exist')
            else:
                user = User.objects.create_user(name, email, password)
                profile = Profile.objects.create(user=user)
                auth.login(request, user)
                return redirect('/')
            
    variableDict.update({'form': form})
    return render(request, 'signup.html', variableDict)

#+str(user)+'.png', 'wb+'
def handle_uploaded_file(f, user):
    url = MEDIA_URL+'uploads/'+str(user)+'.png'
    with open(MEDIA_ROOT+url, 'wb+') as destination:
        for chunk in f.chunks():
            destination.write(chunk)
    return url


# Cтраница профиля
@login_required(login_url='/login')
def profile(request):
    init_data = {'login': request.user.username,
                'email': request.user.email}
    form = ProfileEditForm(init_data, initial=init_data)
    if request.POST:
        form = ProfileEditForm(request.POST, request.FILES, initial=init_data)
        if form.is_valid() and form.has_changed():
            if (request.FILES.get('avatar')):
                url = handle_uploaded_file(request.FILES['avatar'], request.user.id)
                f = open(url[1:], 'rb+')
                content = File(f)
                #content = ContentFile(str(request.user.id)+'.png')
                request.user.profile.avatar.save(url[1:], content)
            request.user.username=form.cleaned_data.get('login')#, #request.user.username),
            request.user.email=form.cleaned_data.get(MEDIA_URL, request.user.email)
            request.user.save()
    variableDict.update({'form': form})
    return render(request, 'profile.html', variableDict)