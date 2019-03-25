# Generated by Django 2.0.3 on 2018-04-02 02:36

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('questions', '0002_answer_answerscount'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='answer',
            name='answersCount',
        ),
        migrations.AddField(
            model_name='question',
            name='answersCount',
            field=models.IntegerField(default=0),
            preserve_default=False,
        ),
    ]
