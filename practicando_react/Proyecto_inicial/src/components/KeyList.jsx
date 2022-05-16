import React, { Fragment, useState } from 'react'

const KeyList = () => {
    const [list] = useState([1, 2, 3, 4, 5, 6])

    return (
        <Fragment>
            <h2>Este es el contenido de la lista:</h2>
            <ul>
                {list.map((element, index) => 
                    <li key={index}>
                        {element}-{index}
                    </li>
                )}
            </ul>
        </Fragment>
    )
}

export default KeyList