# Generated by Django 2.0.3 on 2018-05-22 16:53

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('questions', '0012_remove_answer_title'),
    ]

    operations = [
        migrations.AlterField(
            model_name='profile',
            name='avatar',
            field=models.ImageField(default='questions/uploads/django.sh.png', upload_to='questions/uploads'),
        ),
    ]
