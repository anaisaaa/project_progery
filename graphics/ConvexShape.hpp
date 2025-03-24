////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
//
// Данное программное обеспечение предоставляется "как есть", без каких-либо гарантий.
// Авторы не несут ответственности за любые убытки, вызванные использованием этого ПО.
//
// Разрешается использовать это ПО для любых целей, включая коммерческие приложения,
// а также модифицировать и свободно распространять при соблюдении следующих условий:
//
// 1. Нельзя выдавать себя за автора оригинального ПО;
//    запрещено утверждать, что вы написали оригинальное ПО.
//    При использовании в продукте, указание авторства приветствуется, но не обязательно.
//
// 2. Измененные версии должны быть явно обозначены как таковые
//    и не должны выдаваться за оригинальное ПО.
//
// 3. Данное уведомление не может быть удалено или изменено.
//
////////////////////////////////////////////////////////////

#ifndef SFML_CONVEXSHAPE_HPP
#define SFML_CONVEXSHAPE_HPP

////////////////////////////////////////////////////////////
// Заголовочные файлы
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <vector>

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Специализированная фигура, представляющая выпуклый многоугольник
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API ConvexShape : public Shape
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Конструктор по умолчанию
    ///
    /// \param pointCount Количество вершин многоугольника
    ///
    ////////////////////////////////////////////////////////////
    explicit ConvexShape(std::size_t pointCount = 0);

    ////////////////////////////////////////////////////////////
    /// \brief Установка количества вершин многоугольника
    ///
    /// \a count должен быть больше 2, чтобы задать валидную фигуру.
    ///
    /// \param count Новое количество вершин многоугольника
    ///
    /// \see getPointCount
    ///
    ////////////////////////////////////////////////////////////
    void setPointCount(std::size_t count);

    ////////////////////////////////////////////////////////////
    /// \brief Получение количества вершин многоугольника
    ///
    /// \return Количество вершин многоугольника
    ///
    /// \see setPointCount
    ///
    ////////////////////////////////////////////////////////////
    virtual std::size_t getPointCount() const;

    ////////////////////////////////////////////////////////////
    /// \brief Установка позиции вершины
    ///
    /// Важно помнить, что многоугольник должен оставаться выпуклым,
    /// а вершины должны быть заданы в правильном порядке!
    /// Сначала необходимо вызвать setPointCount, чтобы установить общее
    /// количество вершин. Результат не определен, если \a index выходит
    /// за допустимые границы.
    ///
    /// \param index Индекс изменяемой вершины (в диапазоне [0 .. getPointCount() - 1])
    /// \param point Новая позиция вершины
    ///
    /// \see getPoint
    ///
    ////////////////////////////////////////////////////////////
    void setPoint(std::size_t index, const Vector2f& point);

    ////////////////////////////////////////////////////////////
    /// \brief Получение позиции вершины
    ///
    /// Возвращаемая точка находится в локальных координатах,
    /// то есть трансформации фигуры (позиция, вращение, масштаб)
    /// не учитываются.
    /// Результат не определен, если \a index выходит за допустимые границы.
    ///
    /// \param index Индекс получаемой вершины (в диапазоне [0 .. getPointCount() - 1])
    ///
    /// \return Позиция вершины с указанным индексом
    ///
    /// \see setPoint
    ///
    ////////////////////////////////////////////////////////////
    virtual Vector2f getPoint(std::size_t index) const;

private:

    ////////////////////////////////////////////////////////////
    // Данные-члены
    ////////////////////////////////////////////////////////////
    std::vector<Vector2f> m_points; ///< Вершины, составляющие выпуклый многоугольник
};

} // namespace sf

#endif // SFML_CONVEXSHAPE_HPP

////////////////////////////////////////////////////////////
/// \class sf::ConvexShape
/// \ingroup graphics
///
/// Этот класс наследует все функции sf::Transformable
/// (позиция, вращение, масштаб, границы и т.д.), а также
/// функции sf::Shape (контур, цвет, текстура и т.д.).
///
/// Важно помнить, что выпуклая фигура должна всегда оставаться
/// выпуклой, иначе она может отображаться некорректно.
/// Кроме того, вершины должны быть заданы в правильном порядке;
/// случайный порядок приведет к некорректной форме.
///
/// Пример использования:
/// \code
/// sf::ConvexShape polygon;
/// polygon.setPointCount(3);
/// polygon.setPoint(0, sf::Vector2f(0, 0));
/// polygon.setPoint(1, sf::Vector2f(0, 10));
/// polygon.setPoint(2, sf::Vector2f(25, 5));
/// polygon.setOutlineColor(sf::Color::Red);
/// polygon.setOutlineThickness(5);
/// polygon.setPosition(10, 20);
/// ...
/// window.draw(polygon);
/// \endcode
///
/// \see sf::Shape, sf::RectangleShape, sf::CircleShape
///
////////////////////////////////////////////////////////////
