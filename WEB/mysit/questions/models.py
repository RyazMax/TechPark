from django.db import models
from django.contrib.auth.models import User
# Create your models here.


class ProfileManager(models.Manager):
    def best(self):
        return self.all()[:5]

    def is_exist(self, name, email):
        return User.objects.filter(username=name).count()


class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    rating = models.IntegerField(default=0)
    avatar = models.ImageField(upload_to='uploads', default='questions/uploads/django.sh.png' )

    def __str__(self):
        return self.user.username
    
    objects = ProfileManager()

class TagManager (models.Manager):
    def popular(self):
        return self.all()[:5]
    
    def create_from_list(self, tags):
        for name in tags:
            if not self.filter(title=name).count():
                self.create(title=name)


class Tag (models.Model):
    title = models.CharField(max_length=10)

    def __str__(self):
        return self.title

    objects = TagManager()

class QuestionManager(models.Manager):
    def newest(self):
        return self.order_by('-created')

    def hotest(self):
        return self.order_by('-rating')
    
    def withTag(self, tag):
        return self.filter(tags__title=tag)


class Question(models.Model):
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)
    title = models.CharField(max_length=64)
    text = models.TextField()
    rating = models.IntegerField(default=0)
    created = models.DateTimeField(auto_now_add=True)
    tags = models.ManyToManyField(Tag, blank=True)

    objects = QuestionManager()
    
    def __str__(self):
        return self.title

    def add_tags(self, tags):
        for tag in tags:
            self.tags.add(Tag.objects.filter(title=tag)[0])


class Answer (models.Model): 
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    text = models.TextField()
    rating = models.IntegerField(default=0)
    created = models.DateTimeField(auto_now_add=True)
    is_right = models.BooleanField(default=False)

    def __str__(self):
        return self.question.title

class Like (models.Model):
    author = models.ForeignKey(Profile, on_delete=models.CASCADE)
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    like_t = models.CharField(max_length=1, default='0')

    def __str__(self):
        return self.question.title + ' ' + str(self.author)
