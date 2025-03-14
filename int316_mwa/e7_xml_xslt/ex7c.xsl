<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <body>
                <h2>Entire catalog</h2>
                <table>
                    <thead>
                        <tr>
                            <th>Title</th>
                            <th>Artist</th>
                            <th>Country</th>
                            <th>Company</th>
                            <th>Price</th>
                            <th>Year</th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="catalog/cd">
                            <xsl:apply-templates select="." />
                        </xsl:for-each>
                    </tbody>
                </table>
                <h2>EU catalog</h2>
                <table>
                    <thead>
                        <tr>
                            <th>Title</th>
                            <th>Artist</th>
                            <th>Country</th>
                            <th>Company</th>
                            <th>Price</th>
                            <th>Year</th>
                        </tr>
                    </thead>
                    <tbody>
                        <xsl:for-each select="catalog/cd">
                            <xsl:sort select="title" />
                            <xsl:if test="country = 'EU'">
                                <xsl:apply-templates select="." />
                            </xsl:if>
                        </xsl:for-each>
                    </tbody>
                </table>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="cd">
        <tr>
            <td>
                <xsl:value-of select="title" />
            </td>
            <td>
                <xsl:value-of select="artist" />
            </td>
            <td>
                <xsl:value-of select="country" />
            </td>
            <td>
                <xsl:value-of select="company" />
            </td>
            <td>
                <xsl:choose>
                    <xsl:when test="price &lt; 8">
                        <xsl:apply-templates
                            select="price" />
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="price" />
                    </xsl:otherwise>
                </xsl:choose>
            </td>
            <td>
                <xsl:value-of select="year" />
            </td>
        </tr>
    </xsl:template>

    <xsl:template match="price">
        <span style="background-color: red; color: white;">
            <xsl:value-of select="." />
        </span>
    </xsl:template>
</xsl:stylesheet>
