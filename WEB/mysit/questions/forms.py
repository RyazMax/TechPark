from django import forms

class AskForm(forms.Form):
    title = forms.CharField(
        max_length=100,
        widget=forms.TextInput(
            attrs={ 'class': 'form-control'}
        )
    )
    text = forms.CharField(
        max_length=400,
        widget=forms.Textarea(
        attrs={ 'class' : 'form-control'}
        )
    )
    tags = forms.CharField(
        max_length=150,
        required=False,
        widget=forms.TextInput(
            attrs={ 'class': 'form-control'},
        )
    )


class RegisterForm(forms.Form):
    login = forms.CharField(
        max_length=40,
        label='Login',
        widget=forms.TextInput(
            attrs={ 'class': 'form-control'}
        )
    )
    email = forms.EmailField(
        max_length=40,
        label='Email',
        widget=forms.EmailInput(
            attrs={ 'class': 'form-control'}
        )
    )
    password = forms.CharField(
        max_length=40,
        label='Password',
        widget=forms.PasswordInput(
            attrs={ 'class': 'form-control'}
        )
    )
    rep_password = forms.CharField(
        max_length=40,
        label='Repeat password',
        widget=forms.PasswordInput(
            attrs={ 'class': 'form-control'}
        )
    )


class LoginForm(forms.Form):
    login = forms.CharField(
        max_length=40,
        label='Login',
        widget=forms.TextInput(
            attrs={ 'class': 'form-control'}
        )
    )
    Password = forms.CharField(
        max_length=40,
        widget=forms.PasswordInput(
            attrs={ 'class': 'form-control'}
        )
    )


class ProfileEditForm(forms.Form):
    login = forms.CharField(
        required=False,
        max_length=40,
        label='Login',
        widget=forms.TextInput(
            attrs={ 'class': 'form-control'}
        )
    )
    email = forms.EmailField(
        required=False,
        max_length=40,
        label='Email',
        widget=forms.EmailInput(
            attrs={ 'class': 'form-control'}
        )
    )
    avatar = forms.ImageField(
        required=False,
        label='Avatar',
        widget=forms.FileInput(
            attrs={ 'class': 'form-control askme-higher'}
        )
    )


class AnswerForm(forms.Form):
    textarea = forms.CharField(
        max_length=200,
        widget=forms.Textarea(
            attrs={ 'class': 'askme-textarea'}
        )
    )