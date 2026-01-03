using System;
using System.Collections.Generic;

public abstract class Document
{
    public string Author { get; set; }

    public abstract void Render();
}

public class TextDocument : Document
{
    public string Content { get; set; }

    public override void Render()
    {
        Console.WriteLine($"=== Текстовый документ ===");
        Console.WriteLine($"Автор: {Author}");
        Console.WriteLine($"Содержимое:");
        Console.WriteLine(Content);
        Console.WriteLine("=========================");
    }
}

public class ImageDocument : Document
{
    public string Resolution { get; set; }

    public override void Render()
    {
        Console.WriteLine($"=== Изображение ===");
        Console.WriteLine($"Автор: {Author}");
        Console.WriteLine($"Разрешение: {Resolution}");
        Console.WriteLine("Рендеринг изображения...");
        Console.WriteLine("====================");
    }
}

class Program
{
    static void Main(string[] args)
    {
        List<Document> documents = new List<Document>();

        TextDocument textDoc = new TextDocument
        {
            Author = "Александр Пушкин",
            Content = "Мой дядя самых честных правил,\n" +
                     "Когда не в шутку занемог,\n" +
                     "Он уважать себя заставил\n" +
                     "И лучше выдумать не мог."
        };
        documents.Add(textDoc);

        TextDocument textDoc2 = new TextDocument
        {
            Author = "Лев Толстой",
            Content = "Все счастливые семьи похожи друг на друга,\n" +
                     "каждая несчастливая семья несчастлива по-своему."
        };
        documents.Add(textDoc2);

        ImageDocument imageDoc = new ImageDocument
        {
            Author = "Винсент Ван Гог",
            Resolution = "1920x1080"
        };
        documents.Add(imageDoc);

        ImageDocument imageDoc2 = new ImageDocument
        {
            Author = "Пабло Пикассо",
            Resolution = "800x600"
        };
        documents.Add(imageDoc2);

        Console.WriteLine("=== ДЕМОНСТРАЦИЯ ПОЛИМОРФНОЙ ОБРАБОТКИ ДОКУМЕНТОВ ===\n");

        foreach (Document doc in documents)
        {
            doc.Render();
            Console.WriteLine();
        }

        Console.WriteLine("=== АНАЛИЗ КОЛЛЕКЦИИ ===");
        int textCount = 0;
        int imageCount = 0;

        foreach (Document doc in documents)
        {
            if (doc is TextDocument)
                textCount++;
            else if (doc is ImageDocument)
                imageCount++;
        }

        Console.WriteLine($"Количество текстовых документов: {textCount}");
        Console.WriteLine($"Количество изображений: {imageCount}");
        Console.WriteLine($"Общее количество документов: {documents.Count}");
    }
}
