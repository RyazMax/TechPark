# Generated by Django 2.0.3 on 2018-05-22 14:18

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('questions', '0011_profile_avatar'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='answer',
            name='title',
        ),
    ]