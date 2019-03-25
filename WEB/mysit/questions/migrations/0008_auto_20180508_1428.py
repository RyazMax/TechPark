# Generated by Django 2.0.3 on 2018-05-08 14:28

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('questions', '0007_like_like_t'),
    ]

    operations = [
        migrations.AddField(
            model_name='answer',
            name='is_right',
            field=models.BooleanField(default=False),
        ),
        migrations.AddField(
            model_name='profile',
            name='avatar',
            field=models.ImageField(default=0, upload_to='questions'),
        ),
    ]